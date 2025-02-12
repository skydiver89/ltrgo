package ltrgo

/*
#cgo CFLAGS: -g -w
#cgo linux LDFLAGS: -L/usr/lib/ -lltrapi -lltr27api
#cgo windows LDFLAGS: -L./ltr/libmingw/ -lltrapi -lltr27api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr27api.h>
*/
import (
	"C"
)
import (
	"bytes"
	"encoding/binary"
	"errors"
	"math"
	"time"
	"unsafe"
)

const LTR27_WORD_COUNT = 16

var ErrStop27 = errors.New("can't stop ltr27")
var ErrStart27 = errors.New("can't start ltr27")
var ErrClose27 = errors.New("can't close ltr27")
var ErrInit27 = errors.New("can't init ltr27")
var ErrOpen27 = errors.New("can't open ltr27")
var ErrGetConfig27 = errors.New("can't get config ltr27")
var ErrSetConfig27 = errors.New("can't set config ltr27")
var ErrGetDescription27 = errors.New("can't get description ltr27")
var ErrStuck27 = errors.New("ltr27 stucked")

type LTR27Module struct {
	CommonModule
	ltr27      *C.TLTR27
	frequency  int
	divisor    int
	pseudoTime int64
}

func (m *LTR27Module) Type() string {
	return "LTR27"
}

// Можно вызывать эту функцию только после Start()!!!
func (m *LTR27Module) GetMezzInfo() []string {
	var res []string
	for i := 0; i < C.LTR27_MEZZANINE_NUMBER; i++ {
		res = append(res, C.GoString((*C.char)(unsafe.Pointer(&m.ltr27.ModuleInfo.Mezzanine[i].Name[0]))))
	}
	return res
}

// Минимальная частота - 5Hz
func (m *LTR27Module) SetConfig(frequency int) {
	if frequency < 5 {
		frequency = 5
	}
	m.frequency = frequency
	m.divisor = int(1000.0/float32(m.frequency)) - 1
}

func (m *LTR27Module) Stop() error {
	res := C.LTR27_ADCStop(m.ltr27)
	if res != C.LTR_OK {
		return ErrStop27
	}
	res = C.LTR27_Close(m.ltr27)
	if res != C.LTR_OK {
		return ErrClose27
	}
	return nil
}

func (m *LTR27Module) Start() error {
	if m.frequency == 0 {
		m.SetConfig(5)
	}
	m.ltr27 = new(C.TLTR27)
	res := C.LTR27_Init(m.ltr27)
	if res != C.LTR_OK {
		return ErrInit27
	}
	res = C.LTR27_Open(m.ltr27, C.SADDR_DEFAULT, C.SPORT_DEFAULT, &m.crate[0], C.ushort(m.slot))
	if res != C.LTR_OK {
		return ErrOpen27
	}
	res = C.LTR27_GetConfig(m.ltr27)
	if res != C.LTR_OK {
		return ErrGetConfig27
	}
	res = C.LTR27_GetDescription(m.ltr27, C.LTR27_ALL_DESCRIPTION)
	if res != C.LTR_OK {
		return ErrGetDescription27
	}
	m.ltr27.FrequencyDivisor = C.uchar(m.divisor)
	for i := 0; i < C.LTR27_MEZZANINE_NUMBER; i++ {
		for j := 0; j < 4; j++ {
			mezzDescr := TMezzanineDescription{}
			mezzDescr.unpack(&m.ltr27.ModuleInfo.Mezzanine[i])
			m.ltr27.Mezzanine[i].CalibrCoeff[j] = C.double(mezzDescr.Calibration[j])
		}
	}
	res = C.LTR27_SetConfig(m.ltr27)
	if res != C.LTR_OK {
		return ErrSetConfig27
	}
	res = C.LTR27_ADCStart(m.ltr27)
	if res != C.LTR_OK {
		return ErrStart27
	}
	m.pseudoTime = time.Now().UnixMicro()
	return nil
}

func (m *LTR27Module) GetFrame() (int64, []float32, error) {
	tries := 0
AGAIN:
	var frame []float32
	var buf [LTR27_WORD_COUNT]C.DWORD
	var bbuf [LTR27_WORD_COUNT]C.double
	var curTime int64
	if m.frequency > 100 {
		m.pseudoTime += 1000000 / int64(m.frequency)
		curTime = int64(m.pseudoTime) / 1000
	} else {
		curTime = time.Now().UnixMilli()
	}
	C.LTR27_Recv(m.ltr27, &buf[0], nil, cuint(LTR27_WORD_COUNT), cuint(10000))
	size := cuint(LTR27_WORD_COUNT)
	res := C.LTR27_ProcessData(m.ltr27, &buf[0], &bbuf[0], &size, C.int(1), C.int(1))
	for i := 0; i < LTR27_WORD_COUNT; i++ {
		frame = append(frame, float32(bbuf[i]))
	}
	if res != C.LTR_OK { //Не видел, чтобы это случалось, но на всякий случай
		tries++
		if tries == 10 {
			return curTime, frame, ErrStuck27
		}
		goto AGAIN
	}
	return curTime, frame, nil
}

type TMezzanineDescription struct {
	Active       byte
	Name         [16]byte //C.LTR_DESCR_NAME_LEN
	SerialNumber [16]byte //C.LTR_DESCR_SERIAL_LEN
	Revision     byte
	Calibration  [4]float64 //C.LTR_DESCR_MEZ_CALIB_CNT
	Comment      [256]byte  //C.LTR_DESCR_COMMENT_LEN
}

func (m *TMezzanineDescription) unpack(i *C.TLTR_DESCRIPTION_MEZZANINE) {
	cdata := C.GoBytes(unsafe.Pointer(i), C.sizeof_TLTR_DESCRIPTION_MEZZANINE)
	buf := bytes.NewBuffer(cdata)
	binary.Read(buf, binary.LittleEndian, &m.Active)
	binary.Read(buf, binary.LittleEndian, &m.Name)
	binary.Read(buf, binary.LittleEndian, &m.SerialNumber)
	binary.Read(buf, binary.LittleEndian, &m.Revision)
	binary.Read(buf, binary.LittleEndian, &m.Calibration)
	for i := 0; i < 4; i++ { //C.LTR_DESCR_MEZ_CALIB_CNT
		bits := binary.LittleEndian.Uint64(cdata[36+i*8 : 44+i*8]) //Всё из-за выравнивания структур в либе лкарда
		m.Calibration[i] = math.Float64frombits(bits)
	}
	binary.Read(buf, binary.LittleEndian, &m.Comment)
}

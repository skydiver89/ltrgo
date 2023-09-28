package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi -lltr27api
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
	"unsafe"
)

var ErrStop27 = errors.New("can't stop ltr27")
var ErrStart27 = errors.New("can't start ltr27")
var ErrClose27 = errors.New("can't close ltr27")
var ErrInit27 = errors.New("can't init ltr27")
var ErrOpen27 = errors.New("can't open ltr27")
var ErrGetConfig27 = errors.New("can't get config ltr27")
var ErrSetConfig27 = errors.New("can't set config ltr27")
var ErrGetDescription27 = errors.New("can't get description ltr27")

type LTR27Module struct {
	CommonModule
	ltr27     *C.TLTR27
	frequency int
	divisor   int
}

func (m *LTR27Module) SetConfig(frequency int) {
	m.frequency = frequency
	if frequency >= 4 {
		m.divisor = int(1000.0/float32(m.frequency)) - 1
	} else {
		m.divisor = 249 //4Hz (1000.0/4-1)
	}
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
		m.SetConfig(1)
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
	return nil
}

func (m *LTR27Module) GetFrame() (int64, []float32, error) {
	var curTime int64
	var frame []float32
	return curTime, frame, nil
}

type TMezzanineDescription struct {
	Active       byte
	Name         [C.LTR_DESCR_NAME_LEN]byte
	SerialNumber [C.LTR_DESCR_SERIAL_LEN]byte
	Revision     byte
	Calibration  [C.LTR_DESCR_MEZ_CALIB_CNT]float64
	Comment      [C.LTR_DESCR_COMMENT_LEN]byte
}

func (m *TMezzanineDescription) unpack(i *C.TLTR_DESCRIPTION_MEZZANINE) {
	cdata := C.GoBytes(unsafe.Pointer(i), C.sizeof_TLTR_DESCRIPTION_MEZZANINE)
	buf := bytes.NewBuffer(cdata)
	binary.Read(buf, binary.LittleEndian, &m.Active)
	binary.Read(buf, binary.LittleEndian, &m.Name)
	binary.Read(buf, binary.LittleEndian, &m.SerialNumber)
	binary.Read(buf, binary.LittleEndian, &m.Revision)
	binary.Read(buf, binary.LittleEndian, &m.Calibration)
	for i := 0; i < C.LTR_DESCR_MEZ_CALIB_CNT; i++ {
		bits := binary.LittleEndian.Uint64(cdata[36+i*8 : 44+i*8]) //Всё из-за выравнивания структур в либе лкарда
		m.Calibration[i] = math.Float64frombits(bits)
	}
	binary.Read(buf, binary.LittleEndian, &m.Comment)
}

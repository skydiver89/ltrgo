package ltrgo

/*
#cgo CFLAGS: -g -w
#cgo linux LDFLAGS: -L/usr/lib/ -lltrapi -lltr11api
#cgo windows LDFLAGS: -L./ltr/libmingw/ -lltrapi -lltr11api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr11api.h>
*/
import (
	"C"
)

import (
	"errors"
	"time"
	"unsafe"
)

type LTR11_MODE int

const (
	LTR11_MODE16 LTR11_MODE = 16
	LTR11_MODE32 LTR11_MODE = 32
)

type LTR11_TEST_MODE int

const (
	LTR11_STATE      = C.LTR11_ADCMODE_ACQ
	LTR11_TEST_0067P = C.LTR11_ADCMODE_TEST_U1P
	LTR11_TEST_0067N = C.LTR11_ADCMODE_TEST_U1N
	LTR11_TEST_2500N = C.LTR11_ADCMODE_TEST_U2N
	LTR11_TEST_2500P = C.LTR11_ADCMODE_TEST_U2P
)

type TLTRopt struct {
}

var ErrInit11 = errors.New("can't initialize ltr11")
var ErrOpen11 = errors.New("can't open ltr11")
var ErrGetConfig11 = errors.New("can't get config of ltr11")
var ErrSetAdc11 = errors.New("can't set ADC of ltr11")
var ErrStop11 = errors.New("can't stop ltr11")
var ErrStart11 = errors.New("can't start ltr11")
var ErrClose11 = errors.New("can't close ltr11")
var ErrStuck11 = errors.New("ltr11 stucked")

type LTR11Module struct {
	CommonModule
	ltr11     *C.TLTR11
	mode      LTR11_MODE
	testMode  LTR11_TEST_MODE
	prescaler int
	divider   int
	channel   *C.TLTR
}

func (m *LTR11Module) SetConfig(frequency int, mode LTR11_MODE, testMode LTR11_TEST_MODE) {
	m.mode = mode
	m.testMode = testMode
	prescalerPtr := (*C.int)(unsafe.Pointer(&m.prescaler))
	dividerPtr := (*C.int)(unsafe.Pointer(&m.divider))
	f := 0
	fPtr := (*C.double)(unsafe.Pointer(&f))
	C.LTR11_FindAdcFreqParams(C.double(int(m.mode)*frequency), prescalerPtr, dividerPtr, fPtr)
}

func (m *LTR11Module) Stop() error {
	res := C.LTR11_Stop(m.ltr11)
	if res != C.LTR_OK {
		return ErrStop11
	}
	res = C.LTR11_Close(m.ltr11)
	if res != C.LTR_OK {
		return ErrClose11
	}
	return nil
}

func (m *LTR11Module) Start() error {
	if m.mode == 0 {
		m.SetConfig(1, LTR11_MODE32, LTR11_STATE)
	}

	m.ltr11 = new(C.TLTR11)
	res := C.LTR11_Init(m.ltr11)
	if res != C.LTR_OK {
		return ErrInit11
	}
	res = C.LTR11_Open(m.ltr11, C.SADDR_DEFAULT, C.SPORT_DEFAULT, &m.crate[0], C.int(m.slot))
	if res != C.LTR_OK {
		return ErrOpen11
	}
	res = C.LTR11_GetConfig(m.ltr11)
	if res != C.LTR_OK {
		return ErrGetConfig11
	}
	m.ltr11.StartADCMode = C.LTR11_STARTADCMODE_INT
	m.ltr11.InpMode = C.LTR11_INPMODE_INT
	if m.mode == LTR11_MODE16 {
		m.ltr11.LChQnt = C.int(16)
		for k := 0; k < 16; k++ {
			m.ltr11.LChTbl[k] = C.uchar(k)
		}
	} else {
		m.ltr11.LChQnt = C.int(32)
		for k := 0; k < 32; k++ {
			m.ltr11.LChTbl[k] = C.uchar(k | 0x20)
		}
	}
	m.ltr11.ADCMode = C.int(m.testMode)
	m.ltr11.ADCRate.prescaler = C.int(m.prescaler)
	m.ltr11.ADCRate.divider = C.int(m.divider)
	res = C.LTR11_SetADC(m.ltr11)
	if res != C.LTR_OK {
		return ErrSetAdc11
	}
	res = C.LTR11_Stop(m.ltr11)
	if res != C.LTR_OK {
		return ErrStop11
	}
	res = C.LTR11_Start(m.ltr11)
	if res != C.LTR_OK {
		return ErrStart11
	}
	return nil
}

func (m *LTR11Module) GetFrame() (int64, []float32, error) {
	tries := 0
AGAIN:
	var frame []float32
	var buf [32]C.DWORD
	var bbuf [32]C.double
	curTime := time.Now().UnixMilli()
	C.LTR11_Recv(m.ltr11, &buf[0], nil, cuint(m.mode), cuint(10000))
	size := C.int(m.mode)
	res := C.LTR11_ProcessData(m.ltr11, &buf[0], &bbuf[0], &size, C.int(0), C.int(1))
	for i := 0; i < int(m.mode); i++ {
		frame = append(frame, float32(bbuf[i]))
	}
	if res != C.LTR_OK {
		tries++
		if tries == 10 {
			return curTime, frame, ErrStuck11
		}
		goto AGAIN
	}
	return curTime, frame, nil
}

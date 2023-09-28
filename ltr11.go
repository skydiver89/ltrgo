package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi -lltr11api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr11api.h>
*/
import (
	"C"
)
import (
	"errors"
	"unsafe"
)

type LTR11_MODE int

const (
	LTR11_MODE16 LTR11_MODE = 16
	LTR11_MODE32 LTR11_MODE = 32
)

var ErrInit11 = errors.New("can't initialize ltr11")
var ErrOpen11 = errors.New("can't open ltr11")
var ErrGetConfig11 = errors.New("can't get config of ltr11")
var ErrSetAdc11 = errors.New("can't set ADC of ltr11")
var ErrStop11 = errors.New("can't stop ltr11")
var ErrStart11 = errors.New("can't start ltr11")

type LTR11Module struct {
	CommonModule
	ltr11     *C.TLTR11
	mode      LTR11_MODE
	prescaler int
	divider   int
}

func (m *LTR11Module) SetConfig(frequency int) {
	m.mode = LTR11_MODE32
	if frequency < 4 {
		frequency = 4
	}
	prescalerPtr := (*C.int)(unsafe.Pointer(&m.prescaler))
	dividerPtr := (*C.int)(unsafe.Pointer(&m.divider))
	f := 0
	fPtr := (*C.double)(unsafe.Pointer(&f))
	C.LTR11_FindAdcFreqParams(C.double(32*frequency*2), prescalerPtr, dividerPtr, fPtr)
}

func (m *LTR11Module) Init() error {
	m.SetConfig(1) //Нужно убрать отсюда!!!!

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
	m.ltr11.ADCMode = C.LTR11_ADCMODE_ACQ
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
	var curTime int64
	var frame []float32
	return curTime, frame, nil
}

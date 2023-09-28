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
import "errors"

var ErrStop27 = errors.New("can't stop ltr27")
var ErrClose27 = errors.New("can't close ltr27")

type LTR27Module struct {
	CommonModule
	ltr27     *C.TLTR27
	frequency int
}

func (m *LTR27Module) SetConfig(frequency int) {
	m.frequency = frequency
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
	return nil
}

func (m *LTR27Module) GetFrame() (int64, []float32, error) {
	var curTime int64
	var frame []float32
	return curTime, frame, nil
}

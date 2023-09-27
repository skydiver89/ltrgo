package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi -lltr43api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr43api.h>
*/
import (
	"C"
)
import "errors"

var ErrInit43 = errors.New("can't initialize ltr43")
var ErrOpen43 = errors.New("can't open ltr43")
var ErrConfig43 = errors.New("can't config ltr43")

type LTR43Module struct {
	CommonModule
	ltr43 *C.TLTR43
}

func (m *LTR43Module) Init() error {
	m.ltr43 = new(C.TLTR43)
	res := C.LTR43_Init(m.ltr43)
	if res != C.LTR_OK {
		return ErrInit43
	}
	res = C.LTR43_Open(m.ltr43, C.SADDR_DEFAULT, C.SPORT_DEFAULT, &m.crate[0], C.int(m.slot))
	if res != C.LTR_OK {
		return ErrOpen43
	}
	m.ltr43.IO_Ports.Port1 = 0
	m.ltr43.IO_Ports.Port2 = 0
	m.ltr43.IO_Ports.Port3 = 0
	m.ltr43.IO_Ports.Port4 = 0
	res = C.LTR43_Config(m.ltr43)
	if res != C.LTR_OK {
		return ErrConfig43
	}
	return nil
}

func (m *LTR43Module) GetFrame() {

}

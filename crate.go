package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi -lltr11api -lltr27api -lltr43api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr11api.h>
#include <ltr/include/ltr27api.h>
#include <ltr/include/ltr43api.h>
#include <stdlib.h>
#include <string.h>
*/
import (
	"C"
)
import (
	"errors"
	"unsafe"
)

var ErrInitCrate = errors.New("can't initialize ltr structure")
var ErrOpenCrate = errors.New("can't open connection to ltrd")
var ErrGetCrates = errors.New("can't get crates")
var ErrGetModules = errors.New("can't get modules")

func GetCrateSerials() ([]string, error) {
	ltr := new(C.TLTR)
	res := C.LTR_Init(ltr)
	if res != C.LTR_OK {
		return nil, ErrInitCrate
	}

	res = C.LTR_Open(ltr)
	if res != C.LTR_OK {
		return nil, ErrOpenCrate
	}
	foundCrates := 0
	foundCratesPtr := (*C.uint)(unsafe.Pointer(&foundCrates))
	cratesReturned := 0
	cratesReturnedPtr := (*C.uint)(unsafe.Pointer(&cratesReturned))
	var infoList [C.LTR_CRATES_MAX]C.TLTR_CRATE_INFO
	infoListPtr := (*C.TLTR_CRATE_INFO)(unsafe.Pointer(&infoList))
	var serials [C.LTR_CRATES_MAX][C.LTR_CRATE_SERIAL_SIZE]C.char
	res = C.LTR_GetCratesEx(ltr, C.LTR_CRATES_MAX, C.LTR_GETCRATES_FLAGS_WORKMODE_ONLY, foundCratesPtr, cratesReturnedPtr, &serials[0], infoListPtr)
	if res != C.LTR_OK {
		return nil, ErrGetCrates
	}
	C.LTR_Close(ltr)
	var result []string
	for i := 0; i < foundCrates; i++ {
		result = append(result, C.GoString(&serials[i][0]))
	}
	return result, nil
}

func GetModules(serial string) ([]ModuleInterface, error) {
INIT:
	var modules []ModuleInterface
	var ser [C.LTR_CRATE_SERIAL_SIZE]C.char
	C.strcpy(&ser[0], C.CString(serial))
	ltr := new(C.TLTR)
	res := C.LTR_Init(ltr)
	if res != C.LTR_OK {
		return nil, ErrInitCrate
	}
	ltr.cc = C.CC_CONTROL
	ltr.csn = ser
	res = C.LTR_Open(ltr)
	if res != C.LTR_OK {
		return nil, ErrOpenCrate
	}
	var mid [C.MODULE_MAX]C.WORD
	res = C.LTR_GetCrateModules(ltr, &mid[0])
	if res != C.LTR_OK {
		return nil, ErrGetModules
	}
	for i := 0; i < C.MODULE_MAX; i++ {

		moduleType := mid[i] & 0xFF
		switch moduleType {
		case 11, 27, 43:
			mod := moduleCreator[uint8(moduleType)]()
			mod.setCrate(ltr.csn)
			mod.setSlot(i + 1)
			modules = append(modules, mod)
		}
		if moduleType == 255 { //need to reread crate
			C.LTR_ResetModule(ltr, C.LTR_CRATE_IFACE_UNKNOWN, &ltr.csn[0], C.int(i+1), 0)
			C.LTR_Close(ltr)
			goto INIT
		}
	}
	C.LTR_Close(ltr)
	return modules, nil
}

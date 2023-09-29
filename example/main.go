package main

import (
	"fmt"
	"log"
	"time"

	ltr "github.com/skydiver89/ltrgo"
)

func main() {
	crates, err := ltr.GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
	//fmt.Println(crates)
	var allModules []ltr.ModuleInterface
	for _, crate := range crates {
		fmt.Println("Крейт:", crate)
		modules, err := ltr.GetModules(crate)
		if err != nil {
			log.Fatalln(err)
		}
		allModules = append(allModules, modules...)
	}
	if len(allModules) == 0 {
		log.Fatalln("No modules found")
	}
	for _, module := range allModules {
		switch mod := module.(type) {
		case *ltr.LTR11Module:
			mod.SetConfig(5, ltr.LTR11_MODE32)
		case *ltr.LTR27Module:
			mod.SetConfig(5)
		}
		module.Start()
	}
	for i := 0; i < 10; i++ {
		for _, module := range allModules {
			t, data, _ := module.GetFrame()
			tString := time.Unix(t/1000, (t%1000)*int64(time.Millisecond)).Format("15:04:05")
			fmt.Println(tString, data)
		}
	}
	for _, module := range allModules {
		module.Stop()
	}
}

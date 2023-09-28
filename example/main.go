package main

import (
	"fmt"
	"log"
	"time"

	"github.com/skydiver89/ltrgo"
)

func main() {
	crates, err := GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
	//fmt.Println(crates)
	var allModules []ModuleInterface
	for _, crate := range crates {
		fmt.Println("Крейт:", crate)
		modules, err := GetModules(crate)
		if err != nil {
			log.Fatalln(err)
		}
		allModules = append(allModules, modules...)
	}
	if len(allModules) == 0 {
		log.Fatalln("No modules found")
	}
	for _, module := range allModules {
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

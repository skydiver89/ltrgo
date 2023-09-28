package main

import (
	"fmt"
	"log"
	"time"
)

func main() {
	crates, err := GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
	//fmt.Println(crates)
	var allModules []ModuleInterface
	for _, crate := range crates {
		fmt.Println(crate)
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
		go module.GetFrame()
	}
	time.Sleep(time.Second * 5)
	for _, module := range allModules {
		module.Stop()
	}
}

package main

type LTR27Module struct {
	CommonModule
}

func (m *LTR27Module) Init() error {
	return nil
}

func (m *LTR27Module) GetFrame() (int64, []float32, error) {
	var curTime int64
	var frame []float32
	return curTime, frame, nil
}

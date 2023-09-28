package main

type LTR11Module struct {
	CommonModule
}

func (m *LTR11Module) Init() error {
	return nil
}

func (m *LTR11Module) GetFrame() (int64, []float32, error) {
	var curTime int64
	var frame []float32
	return curTime, frame, nil
}

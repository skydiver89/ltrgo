# Описание  
Go-bindings для библиотек LTR фирмы LCard  
Поддерживаются только платы LTR27, LTR11, LTR43  
# Сборка  
Собирал пример только на Linux. Но работает кросскомпиляция под win32  
Чтобы собрать пример нужно выполнить следующее:  
## Под Linux  
go build  
## Под Windows  
Должен быть установлен MinGW  
CGO_ENABLED=1 CC=i686-w64-mingw32-gcc GOOS=windows GOARCH=386 go build  
Рядом с собранной программой положить dll из ltr/dll  

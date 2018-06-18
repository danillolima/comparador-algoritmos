Software que recebe uma entrada de números e ordena eles usando vários algoritmos diferentes e mostra gráficos .

Requisitos:
- gcc $version>=4  
- windows(win32) ou unix(gtk)

	Pra compilar no windows usando bibliotecas dinâmicas:
	gcc -I iup/include -I iup -I cd/include -L cd -L iup order.c main.c -o main.exe -liup_plot -liupcontrols -liup -lcd -lgdi32 -luser32 -lcomdlg32 -lcomctl32 -luuid -lole32
### Exemplo
![Telas](https://raw.githubusercontent.com/danillolima/comparador-algoritmos/master/docs/telas.png)

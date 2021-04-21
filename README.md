Software que recebe uma entrada de números, ordena eles usando vários algoritmos diferentes e mostra graficamente algumas comparações entre os diferentes algoritmos de ordenação implementados.

Requisitos:
- GCC --version >= 4.0 (Testado apenas no GCC 6.3.0)
- Windows(Win32) ou Unix(GTK)

	Pra compilar no windows usando bibliotecas dinâmicas:
	gcc -I iup/include -I iup -I cd/include -L cd -L iup order.c main.c -o main.exe -liup_plot -liupcontrols -liup -lcd -lgdi32 -luser32 -lcomdlg32 -lcomctl32 -luuid -lole32
### Exemplo
![Telas](https://raw.githubusercontent.com/danillolima/comparador-algoritmos/master/docs/telas.png)

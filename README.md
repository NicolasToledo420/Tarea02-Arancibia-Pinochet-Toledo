Leonardo Esteban Arancibia Vicencio - leonardo.arancibia@alumnos.uv.cl
Augusto Ignacio Pinochet Contreras - augusto.pinochet@alumnos.uv.cl
Nicolás Ignacio Toledo Toledo - nicolas.toledo@alumnos.uv.cl

//Descripcion del funcionamiento del codigo: El codigo muestra en un navegador web, las 3 paginas requeridas, además, si no encuentra el HTML requerido, retorna el error 404 en un archivo HTML.

//COMO COMPILAR EL CODIGO:
	***EN CONSOLA: ***
	git clone https://github.com/NicolasToledo420/Tarea02-Arancibia-Pinochet-Toledo.git
	cd Tarea02-Arancibia-Pinochet-Toledo
	cd src
	make clean
	make
	./echoServer 8081
	***LUEGO DE CONSOLA, EN NAVEGADOR WEB: ***
	127.0.0.200:8081/1.html
	127.0.0.200:8081/2.html
	127.0.0.200:8081/3.html
	127.0.0.200:8081/4.html --> Retorna ERROR 404 NOT FOUND

// 1. Instalar MySQL en su m�quina (si no est� instalado ya).
//    - Si est� en Linux, puede instalarlo con: sudo apt-get install mysql-server
//    - Si est� en Windows, debe descargar MySQL desde su p�gina oficial.

// 2. Asegurarse de tener la biblioteca de cliente MySQL para C instalada:
//    En Linux, puede instalarla con:
//    sudo apt-get install libmysqlclient-dev

// 3. Modificar las credenciales de conexi�n en el c�digo:
//    Dentro del c�digo, se encuentra esta l�nea:
//    mysql_real_connect(conn, "localhost", "root", "password", "Intelligentglasses", 0, NULL, 0);
//    Deber� cambiar "root", "password" y "Intelligentglasses" con las credenciales correctas de su instalaci�n MySQL.

// 4. Compilar el c�digo:
//    En una terminal, navegue hasta la carpeta donde guard� el archivo .c, luego ejecute:
//    Para Linux o macOS:
//    gcc -o programa programa.c -lmysqlclient
//    Para Windows, si usa MinGW, use:
//    gcc -o programa programa.c -lmysqlclient

// 5. Ejecutar el programa:
//    En la terminal, una vez compilado, ejecute el siguiente comando:
//    ./programa

//    Esto iniciar� el programa, lo conectar� a la base de datos MySQL, realizar� consultas e inserciones, y mostrar� los resultados.

// 6. Verificar que el programa se haya ejecutado correctamente y que se haya conectado a la base de datos.
//    Si todo est� bien, el programa mostrar� los resultados de las consultas, como los productos y componentes.

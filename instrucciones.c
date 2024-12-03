// 1. Instalar MySQL en su máquina (si no está instalado ya).
//    - Si está en Linux, puede instalarlo con: sudo apt-get install mysql-server
//    - Si está en Windows, debe descargar MySQL desde su página oficial.

// 2. Asegurarse de tener la biblioteca de cliente MySQL para C instalada:
//    En Linux, puede instalarla con:
//    sudo apt-get install libmysqlclient-dev

// 3. Modificar las credenciales de conexión en el código:
//    Dentro del código, se encuentra esta línea:
//    mysql_real_connect(conn, "localhost", "root", "password", "Intelligentglasses", 0, NULL, 0);
//    Deberá cambiar "root", "password" y "Intelligentglasses" con las credenciales correctas de su instalación MySQL.

// 4. Compilar el código:
//    En una terminal, navegue hasta la carpeta donde guardó el archivo .c, luego ejecute:
//    Para Linux o macOS:
//    gcc -o programa programa.c -lmysqlclient
//    Para Windows, si usa MinGW, use:
//    gcc -o programa programa.c -lmysqlclient

// 5. Ejecutar el programa:
//    En la terminal, una vez compilado, ejecute el siguiente comando:
//    ./programa

//    Esto iniciará el programa, lo conectará a la base de datos MySQL, realizará consultas e inserciones, y mostrará los resultados.

// 6. Verificar que el programa se haya ejecutado correctamente y que se haya conectado a la base de datos.
//    Si todo está bien, el programa mostrará los resultados de las consultas, como los productos y componentes.

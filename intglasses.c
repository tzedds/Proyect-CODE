#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Instrucciones para conectarse a la base de datos

// 1. Aseg�rate de tener MySQL instalado en tu computadora.
// 2. Instala la biblioteca cliente de MySQL para C. En sistemas basados en Linux, usa:
//    sudo apt-get install libmysqlclient-dev

// 3. Crea tu base de datos 'Intelligentglasses' en MySQL (si a�n no est� creada) y
//    carga las tablas que necesitas usar (como 'Productos').
// 4. Cambia las credenciales de la base de datos en el siguiente bloque de c�digo
//    seg�n tu configuraci�n de MySQL.

// Funci�n para realizar la conexi�n a la base de datos MySQL
MYSQL *connect_to_database() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar la conexi�n: %s\n", mysql_error(conn));
        exit(1);  // Termina el programa si no puede inicializar la conexi�n
    }

    // Cambia los par�metros de la siguiente l�nea con tus credenciales de MySQL:
    // "localhost" -> la direcci�n del servidor MySQL (en este caso, local)
    // "root" -> el usuario de MySQL
    // "password" -> la contrase�a de tu usuario de MySQL
    // "Intelligentglasses" -> el nombre de la base de datos que deseas usar
    conn = mysql_real_connect(conn, "localhost", "root", "password", "Intelligentglasses", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(conn));
        exit(1);  // Termina el programa si no puede conectar a la base de datos
    }
    return conn;  // Retorna la conexi�n exitosa
}

// Funci�n para realizar una consulta SELECT y mostrar los resultados
void select_data(MYSQL *conn) {
    const char *query = "SELECT * FROM Productos";  // Consulta SQL para seleccionar productos
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Consulta fallida: %s\n", mysql_error(conn));  // Muestra el error si la consulta falla
        exit(1);  // Termina el programa si la consulta no se ejecuta correctamente
    }

    MYSQL_RES *result = mysql_store_result(conn);  // Almacena el resultado de la consulta
    if (result == NULL) {
        fprintf(stderr, "Error al obtener resultados: %s\n", mysql_error(conn));  // Error al obtener resultados
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {  // Recorre los resultados
        printf("Producto: %s\n", row[1]);  // Muestra el nombre del producto (columna 1)
    }
    mysql_free_result(result);  // Libera la memoria utilizada por el resultado
}

// Funci�n para insertar datos en la tabla Productos
void insert_data(MYSQL *conn) {
    const char *insert_query = "INSERT INTO Productos (nombre, descripcion, precio, fecha_lanzamiento, stock, categoria) VALUES ('Lentes Inteligentes', 'Lentes con tecnolog�a avanzada', 2999.99, '2024-05-01', 50, 'Tecnolog�a')";
    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "Error al insertar datos: %s\n", mysql_error(conn));  // Muestra el error si la inserci�n falla
        exit(1);  // Termina el programa si la inserci�n no se realiza correctamente
    }
    printf("Nuevo producto insertado correctamente.\n");
}

// Funci�n para cerrar la conexi�n a la base de datos
void close_connection(MYSQL *conn) {
    mysql_close(conn);  // Cierra la conexi�n con MySQL
}

int main() {
    // 1. Aseg�rate de que MySQL est� ejecut�ndose en tu computadora
    // 2. Compila y ejecuta este programa. Para ello, sigue las instrucciones de compilaci�n m�s abajo.

    // Conectar a la base de datos
    MYSQL *conn = connect_to_database();

    // Realizar consulta SELECT
    printf("Seleccionando datos de la tabla Productos...\n");
    select_data(conn);

    // Insertar un nuevo producto
    printf("\nInsertando un nuevo producto...\n");
    insert_data(conn);

    // Cerrar la conexi�n a la base de datos
    close_connection(conn);
    return 0;
}

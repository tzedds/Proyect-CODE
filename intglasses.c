#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Instrucciones para conectarse a la base de datos

// 1. Asegúrate de tener MySQL instalado en tu computadora.
// 2. Instala la biblioteca cliente de MySQL para C. En sistemas basados en Linux, usa:
//    sudo apt-get install libmysqlclient-dev

// 3. Crea tu base de datos 'Intelligentglasses' en MySQL (si aún no está creada) y
//    carga las tablas que necesitas usar (como 'Productos').
// 4. Cambia las credenciales de la base de datos en el siguiente bloque de código
//    según tu configuración de MySQL.

// Función para realizar la conexión a la base de datos MySQL
MYSQL *connect_to_database() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar la conexión: %s\n", mysql_error(conn));
        exit(1);  // Termina el programa si no puede inicializar la conexión
    }

    // Cambia los parámetros de la siguiente línea con tus credenciales de MySQL:
    // "localhost" -> la dirección del servidor MySQL (en este caso, local)
    // "root" -> el usuario de MySQL
    // "password" -> la contraseña de tu usuario de MySQL
    // "Intelligentglasses" -> el nombre de la base de datos que deseas usar
    conn = mysql_real_connect(conn, "localhost", "root", "password", "Intelligentglasses", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(conn));
        exit(1);  // Termina el programa si no puede conectar a la base de datos
    }
    return conn;  // Retorna la conexión exitosa
}

// Función para realizar una consulta SELECT y mostrar los resultados
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

// Función para insertar datos en la tabla Productos
void insert_data(MYSQL *conn) {
    const char *insert_query = "INSERT INTO Productos (nombre, descripcion, precio, fecha_lanzamiento, stock, categoria) VALUES ('Lentes Inteligentes', 'Lentes con tecnología avanzada', 2999.99, '2024-05-01', 50, 'Tecnología')";
    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "Error al insertar datos: %s\n", mysql_error(conn));  // Muestra el error si la inserción falla
        exit(1);  // Termina el programa si la inserción no se realiza correctamente
    }
    printf("Nuevo producto insertado correctamente.\n");
}

// Función para cerrar la conexión a la base de datos
void close_connection(MYSQL *conn) {
    mysql_close(conn);  // Cierra la conexión con MySQL
}

int main() {
    // 1. Asegúrate de que MySQL está ejecutándose en tu computadora
    // 2. Compila y ejecuta este programa. Para ello, sigue las instrucciones de compilación más abajo.

    // Conectar a la base de datos
    MYSQL *conn = connect_to_database();

    // Realizar consulta SELECT
    printf("Seleccionando datos de la tabla Productos...\n");
    select_data(conn);

    // Insertar un nuevo producto
    printf("\nInsertando un nuevo producto...\n");
    insert_data(conn);

    // Cerrar la conexión a la base de datos
    close_connection(conn);
    return 0;
}

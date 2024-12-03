#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Inicializar la conexión a la base de datos
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar MySQL: %s\n", mysql_error(conn));
        exit(1);
    }

    // Conectar a la base de datos
    if (mysql_real_connect(conn, "localhost", "root", "password", "Intelligentglasses", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        exit(1);
    }

    // Insertar datos de prueba en la tabla Proveedores
    const char *insert_proveedor = "INSERT INTO Proveedores (nombre, contacto, pais, calificacion, fecha_registro) VALUES "
                                  "('Proveedor A', 'glasses@proveedora.com', 'México', 4.5, '2022-01-15'), "
                                  "('Proveedor B', 'glasses@proveedorb.com', 'China', 4.8, '2023-02-10'), "
                                  "('Proveedor C', 'glasses@proveedorc.com', 'EE.UU.', 4.3, '2020-06-22');";
    if (mysql_query(conn, insert_proveedor)) {
        fprintf(stderr, "Error en la inserción de proveedores: %s\n", mysql_error(conn));
    }

    // Insertar datos de prueba en la tabla Productos
    const char *insert_productos = "INSERT INTO Productos (nombre, descripcion, precio, fecha_lanzamiento, stock, categoria) VALUES "
                                  "('Lentes Autoajuste 1.0', 'Lentes con ajuste inteligente básico', 1999.99, '2023-05-20', 150, 'Autoajuste'), "
                                  "('Lentes Bluetooth Plus', 'Lentes con conectividad Bluetooth avanzada', 2999.99, '2023-08-10', 100, 'Conectividad'), "
                                  "('Lentes Smart Filters', 'Lentes con filtros inteligentes de luz', 2499.99, '2024-01-15', 200, 'Filtros');";
    if (mysql_query(conn, insert_productos)) {
        fprintf(stderr, "Error en la inserción de productos: %s\n", mysql_error(conn));
    }

    // Insertar datos de prueba en la tabla Componentes
    const char *insert_componentes = "INSERT INTO Componentes (nombre, tipo, proveedor_id, costo, especificaciones) VALUES "
                                    "('Sensor de luz', 'Sensor', 1, 50.00, 'Detecta niveles de luminosidad'), "
                                    "('Bluetooth v5.0', 'Conectividad', 2, 75.00, 'Compatibilidad avanzada'), "
                                    "('Marco ajustable', 'Estructura', 3, 120.00, 'Autoajuste ergonómico');";
    if (mysql_query(conn, insert_componentes)) {
        fprintf(stderr, "Error en la inserción de componentes: %s\n", mysql_error(conn));
    }

    // Aquí seguirías insertando datos para otras tablas si es necesario

    // Consultar y mostrar datos insertados
    const char *select_query = "SELECT nombre, descripcion FROM Productos";
    if (mysql_query(conn, select_query)) {
        fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error al recuperar el resultado: %s\n", mysql_error(conn));
        exit(1);
    }

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Producto: %s - Descripción: %s\n", row[0], row[1]);
    }

    // Liberar los resultados y cerrar la conexión
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

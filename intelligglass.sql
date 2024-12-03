-- Crear la base de datos
CREATE DATABASE Intelligentglasses;
USE Intelligentglasses;

-- Tabla de Proveedores
-- Registra información sobre los proveedores de componentes, incluyendo calificación y país de origen.
CREATE TABLE Proveedores (
    proveedor_id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    contacto VARCHAR(100),
    pais VARCHAR(50),
    calificacion DECIMAL(3, 2),
    fecha_registro DATE
);

-- Tabla de Productos
-- Contiene información sobre los productos fabricados, incluyendo nombre, precio, categoría y stock.
CREATE TABLE Productos (
    producto_id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    descripcion TEXT,
    precio DECIMAL(10, 2),
    fecha_lanzamiento DATE,
    stock INT,
    categoria VARCHAR(50)
);

-- Tabla de Componentes
-- Lista los componentes utilizados para fabricar productos, asociados a un proveedor.
CREATE TABLE Componentes (
    componente_id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    tipo VARCHAR(50),
    proveedor_id INT,
    costo DECIMAL(10, 2),
    especificaciones TEXT,
    FOREIGN KEY (proveedor_id) REFERENCES Proveedores(proveedor_id)
);

-- Tabla de Clientes
-- Almacena información de los clientes, incluidas sus preferencias y compras previas.
CREATE TABLE Clientes (
    cliente_id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    contacto VARCHAR(100),
    direccion VARCHAR(255),
    historial_compras TEXT,
    preferencia_contacto VARCHAR(50)
);

-- Relación entre Productos y Componentes
-- Representa la asociación entre un producto y sus componentes necesarios, incluyendo la cantidad.
CREATE TABLE Producto_Componentes (
    producto_id INT,
    componente_id INT,
    cantidad INT DEFAULT 1,
    PRIMARY KEY (producto_id, componente_id),
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id),
    FOREIGN KEY (componente_id) REFERENCES Componentes(componente_id)
);

-- Tabla de Ventas
-- Registra las ventas realizadas, enlazando productos con clientes y calculando el total pagado.
CREATE TABLE Ventas (
    venta_id INT AUTO_INCREMENT PRIMARY KEY,
    producto_id INT,
    cliente_id INT,
    fecha_venta DATE,
    cantidad INT,
    precio_total DECIMAL(10, 2),
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id),
    FOREIGN KEY (cliente_id) REFERENCES Clientes(cliente_id)
);

-- Tabla de Órdenes de Producción
-- Detalla las órdenes de producción realizadas, con costos estimados, fechas y estado.
CREATE TABLE Ordenes_Produccion (
    orden_id INT AUTO_INCREMENT PRIMARY KEY,
    producto_id INT,
    cantidad INT,
    fecha_inicio DATE,
    fecha_fin DATE,
    estado VARCHAR(50),
    costo_estimado DECIMAL(10, 2),
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id)
);

-- Tabla de Inventario
-- Controla los niveles de stock de cada producto y define valores mínimos y máximos.
CREATE TABLE Inventario (
    inventario_id INT AUTO_INCREMENT PRIMARY KEY,
    producto_id INT,
    stock_actual INT,
    stock_minimo INT,
    stock_maximo INT,
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id)
);

-- Tabla de Analítica
-- Almacena métricas y comentarios sobre el desempeño de los productos (ventas, ingresos, etc.).
CREATE TABLE Analitica (
    analitica_id INT AUTO_INCREMENT PRIMARY KEY,
    fecha DATE,
    producto_id INT,
    metricas JSON,
    comentarios TEXT,
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id)
);

-- Tabla de Diseño de Producto
-- Documenta el diseño, las versiones y especificaciones técnicas de los productos.
CREATE TABLE Diseno_Producto (
    diseno_id INT AUTO_INCREMENT PRIMARY KEY,
    producto_id INT,
    version VARCHAR(10),
    fecha_creacion DATE,
    especificaciones TEXT,
    FOREIGN KEY (producto_id) REFERENCES Productos(producto_id)
);

-- Insertar datos en Proveedores
INSERT INTO Proveedores (nombre, contacto, pais, calificacion, fecha_registro) VALUES
('Proveedor A', 'glasses@proveedora.com', 'México', 4.5, '2022-01-15'),
('Proveedor B', 'glasses@proveedorb.com', 'China', 4.8, '2023-02-10'),
('Proveedor C', 'glasses@proveedorc.com', 'EE.UU.', 4.3, '2020-06-22');

-- Insertar datos en Productos
INSERT INTO Productos (nombre, descripcion, precio, fecha_lanzamiento, stock, categoria) VALUES
('Lentes Autoajuste 1.0', 'Lentes con ajuste inteligente básico', 1999.99, '2023-05-20', 150, 'Autoajuste'),
('Lentes Bluetooth Plus', 'Lentes con conectividad Bluetooth avanzada', 2999.99, '2023-08-10', 100, 'Conectividad'),
('Lentes Smart Filters', 'Lentes con filtros inteligentes de luz', 2499.99, '2024-01-15', 200, 'Filtros');

-- Insertar datos en Componentes
INSERT INTO Componentes (nombre, tipo, proveedor_id, costo, especificaciones) VALUES
('Sensor de luz', 'Sensor', 1, 50.00, 'Detecta niveles de luminosidad'),
('Bluetooth v5.0', 'Conectividad', 2, 75.00, 'Compatibilidad avanzada'),
('Marco ajustable', 'Estructura', 3, 120.00, 'Autoajuste ergonómico');

-- Insertar datos en Clientes
INSERT INTO Clientes (nombre, contacto, direccion, historial_compras, preferencia_contacto) VALUES
('Juan Pérez', 'juanperez@gmail.com', 'Calle 123, CDMX', 'Lentes Autoajuste 1.0', 'Email'),
('Ana López', 'ana.lopez@hotmail.com', 'Av. Reforma 456, Monterrey', '', 'Teléfono'),
('Carlos Ramírez', 'carlosr@gmail.com', 'Calle 789, Guadalajara', 'Lentes Smart Filters', 'Email');

-- Insertar datos en Producto_Componentes
INSERT INTO Producto_Componentes (producto_id, componente_id, cantidad) VALUES
(1, 1, 2),
(1, 3, 1),
(2, 2, 1),
(3, 1, 1),
(3, 3, 1);

-- Insertar datos en Ventas
INSERT INTO Ventas (producto_id, cliente_id, fecha_venta, cantidad, precio_total) VALUES
(1, 1, '2023-06-15', 1, 1999.99),
(3, 3, '2024-02-01', 2, 4999.98);

-- Insertar datos en Ordenes_Produccion
INSERT INTO Ordenes_Produccion (producto_id, cantidad, fecha_inicio, fecha_fin, estado, costo_estimado) VALUES
(1, 50, '2023-01-01', '2023-02-01', 'Completada', 5000.00),
(2, 30, '2023-07-01', '2023-08-01', 'Completada', 2250.00);

-- Insertar datos en Inventario
INSERT INTO Inventario (producto_id, stock_actual, stock_minimo, stock_maximo) VALUES
(1, 150, 50, 300),
(2, 100, 30, 200),
(3, 200, 70, 400);

-- Insertar datos en Analitica
INSERT INTO Analitica (fecha, producto_id, metricas, comentarios) VALUES
('2023-07-01', 1, '{"ventas_mes": 25, "ingresos": 49999.75}', 'Buen desempeño inicial'),
('2023-12-01', 3, '{"ventas_mes": 40, "ingresos": 99999.60}', 'Alta aceptación');

-- Insertar datos en Diseño de Producto
INSERT INTO Diseno_Producto (producto_id, version, fecha_creacion, especificaciones) VALUES
(1, 'v1.0', '2022-11-15', 'Diseño inicial con autoajuste básico'),
(2, 'v1.1', '2023-04-20', 'Incluye Bluetooth v5.0 con compatibilidad avanzada');

-- Mostrar productos vendidos con sus componentes y clientes
SELECT 
    v.venta_id,
    p.nombre AS producto,
    c.nombre AS cliente,
    comp.nombre AS componente,
    pc.cantidad AS cantidad_componente,
    v.fecha_venta,
    v.cantidad AS cantidad_vendida,
    v.precio_total
FROM Ventas v
JOIN Productos p ON v.producto_id = p.producto_id
JOIN Clientes c ON v.cliente_id = c.cliente_id
JOIN Producto_Componentes pc ON p.producto_id = pc.producto_id
JOIN Componentes comp ON pc.componente_id = comp.componente_id;

-- Verificar el estado de inventario
SELECT 
    i.producto_id,
    p.nombre AS producto,
    i.stock_actual,
    i.stock_minimo,
    i.stock_maximo,
    (i.stock_actual - i.stock_minimo) AS stock_sobrante
FROM Inventario i
JOIN Productos p ON i.producto_id = p.producto_id
WHERE i.stock_actual < i.stock_maximo;

-- Calcular costos y beneficios de órdenes de producción
SELECT 
    op.orden_id,
    p.nombre AS producto,
    op.cantidad,
    op.costo_estimado,
    SUM(v.precio_total) AS ingresos,
    SUM(v.precio_total) - op.costo_estimado AS beneficio
FROM Ordenes_Produccion op
LEFT JOIN Ventas v ON op.producto_id = v.producto_id
JOIN Productos p ON op.producto_id = p.producto_id
GROUP BY op.orden_id;


-- Consultar métricas de desempeño por producto (BI)
SELECT 
    p.nombre AS producto,
    a.metricas,
    a.comentarios
FROM Analitica a
JOIN Productos p ON a.producto_id = p.producto_id
WHERE a.fecha >= '2023-01-01';


-- Obtener el historial de compras de un cliente específico
SELECT 
    c.nombre AS cliente,
    c.contacto,
    p.nombre AS producto,
    v.fecha_venta,
    v.cantidad,
    v.precio_total
FROM Ventas v
JOIN Clientes c ON v.cliente_id = c.cliente_id
JOIN Productos p ON v.producto_id = p.producto_id
WHERE c.nombre = 'Juan Pérez'; -- Cambia el nombre según el cliente que quieras consultar









-- Consultar el estado del inventario para productos con bajo stock
SELECT 
    p.nombre AS producto,
    i.stock_actual,
    i.stock_minimo,
    (i.stock_minimo - i.stock_actual) AS faltante
FROM Inventario i
JOIN Productos p ON i.producto_id = p.producto_id
WHERE i.stock_actual < i.stock_minimo;

SET FOREIGN_KEY_CHECKS = 0;  -- Desactiva temporalmente las restricciones de clave foránea
DROP TABLE IF EXISTS Proveedores, Productos, Componentes, Clientes, Producto_Componentes, Ventas, Ordenes_Produccion, Inventario, Analitica, Diseno_Producto;
SET FOREIGN_KEY_CHECKS = 1;  -- Vuelve a activar las restricciones de clave foránea

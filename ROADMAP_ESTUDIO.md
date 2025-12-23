# 🗺️ ROADMAP DE ESTUDIO - DEFENSA DEL PROYECTO

## 📋 ESTRUCTURA DEL PROYECTO

### **FASE 1: FUNDAMENTOS (Base del proyecto)**
✅ **1. Entidad.h / Entidad.cpp** - Clase base abstracta
- Herencia y polimorfismo
- Atributos protegidos
- Métodos virtuales puros

---

### **FASE 2: ENTIDADES DEL JUEGO (Heredan de Entidad)**

**2. Jugador.h / Jugador.cpp** ⭐ (MÁS IMPORTANTE)
- Herencia múltiple (Entidad + sf::Drawable)
- Sistema de animaciones
- Física y movimiento
- Sistema de vidas y puntaje
- Colisiones con plataformas

**3. Enemigo.h / Enemigo.cpp**
- Herencia múltiple (Entidad + sf::Drawable)
- Sistema de patrullaje
- Animaciones
- Sistema de muerte/desaparición

**4. Meta.h / Meta.cpp**
- Herencia múltiple (Entidad + sf::Drawable)
- Detección de llegada del jugador
- Cambio de estado visual

**5. Plataforma.h / Plataforma.cpp**
- Herencia de sf::Drawable
- Colisiones estáticas
- Representación visual

---

### **FASE 3: GESTIÓN DE NIVELES**

**6. Colisiones.h / Colisiones.cpp**
- Clase estática
- Manejo de colisiones jugador-plataforma
- Manejo de colisiones jugador-enemigo

**7. Nivel.h / Nivel.cpp**
- Composición (tiene Jugador, Plataformas, Enemigos, Meta)
- Gestión del nivel 1
- Verificación de victoria/derrota

**8. Nivel2.h / Nivel2.cpp**
- Similar a Nivel pero nivel 2
- Diferentes posiciones de plataformas/enemigos

**9. Nivel3.h / Nivel3.cpp**
- Similar a Nivel pero nivel 3
- Nivel final del juego

---

### **FASE 4: INTERFAZ Y MENÚS**

**10. EstadosJuego.h** (enum)
- Enum de estados del juego
- MENU, NIVEL_START, JUGANDO, GAME_OVER, VICTORIA

**11. Menu.h / Menu.cpp**
- Pantalla de inicio
- Detección de eventos
- Herencia de sf::Drawable

**12. NivelStart.h / NivelStart.cpp**
- Pantalla de transición entre niveles
- Temporizador automático
- Muestra "NIVEL X"

**13. Puntaje.h / Puntaje.cpp**
- Muestra puntaje, vidas y tiempo
- Herencia de sf::Drawable
- Actualización en tiempo real

**14. GameOver.h / GameOver.cpp**
- Pantalla de derrota
- Muestra mejores puntajes
- Gestión de eventos

**15. Victoria.h / Victoria.cpp**
- Pantalla de victoria final
- Muestra puntaje final
- Gestión de eventos

---

### **FASE 5: UTILIDADES**

**16. Background.h / Background.cpp**
- Manejo de fondos de pantalla
- Herencia de sf::Drawable
- Carga de texturas

**17. GestorArchivos.h / GestorArchivos.cpp**
- Manejo de archivos binarios
- Guardado y lectura de puntajes
- Operaciones de archivo (fopen, fread, fwrite, fclose)

---

### **FASE 6: ENUMS Y CONSTANTES**

**18. EstadoAnimacionJugador.h** (enum)
- IDLE, CAMINANDO, SALTANDO

**19. EstadoAnimacionEnemigo.h** (enum)
- IDLE, CAMINANDO

---

### **FASE 7: FLUJO PRINCIPAL**

**20. main.cpp** ⭐ (MUY IMPORTANTE)
- Bucle principal del juego
- Máquina de estados
- Gestión de transiciones entre estados
- Puntaje acumulado entre niveles

---

## 📚 ORDEN DE ESTUDIO RECOMENDADO

### **DÍA 1: Fundamentos y Entidades Principales**
1. ✅ Entidad (YA VISTO)
2. Jugador (completo, muy importante)
3. Plataforma (simple, buena para entender herencia de sf::Drawable)

### **DÍA 2: Entidades y Colisiones**
4. Enemigo
5. Meta
6. Colisiones

### **DÍA 3: Niveles**
7. Nivel (completo)
8. Nivel2 (similar a Nivel)
9. Nivel3 (similar a Nivel)

### **DÍA 4: Interfaz**
10. EstadosJuego (enum)
11. Menu
12. NivelStart
13. Puntaje

### **DÍA 5: Pantallas Finales y Utilidades**
14. GameOver
15. Victoria
16. Background
17. GestorArchivos

### **DÍA 6: Enums y Main**
18. EstadoAnimacionJugador
19. EstadoAnimacionEnemigo
20. main.cpp (completo, muy importante)

---

## 🎯 CONCEPTOS CLAVE POR ARCHIVO

### **Entidad**
- Clase abstracta
- Herencia
- Polimorfismo
- Métodos virtuales puros
- Protected vs Private

### **Jugador**
- Herencia múltiple
- Override de métodos virtuales
- Sistema de animaciones con sprites
- Física (gravedad, velocidad)
- Colisiones
- Encapsulamiento

### **Enemigo**
- Patrullaje (movimiento automático)
- Estados de animación
- Sistema de muerte

### **Nivel**
- Composición (tiene otras clases)
- Gestión de arrays
- Verificación de condiciones de juego

### **main.cpp**
- Máquina de estados
- Bucle principal del juego
- Gestión de eventos
- Transiciones entre estados

---

## ❓ PREGUNTAS TÍPICAS DEL PROFESOR

### **Sobre Entidad:**
- ¿Por qué es abstracta?
- ¿Qué es un método virtual puro?
- ¿Por qué protected y no private?
- ¿Qué es polimorfismo?

### **Sobre Jugador:**
- ¿Cómo funciona la herencia múltiple?
- ¿Qué hace override?
- ¿Cómo funciona el sistema de animaciones?
- ¿Cómo se manejan las colisiones?

### **Sobre Nivel:**
- ¿Qué es composición?
- ¿Cómo se relaciona con Jugador?
- ¿Cómo verifica si el nivel está completo?

### **Sobre main.cpp:**
- ¿Cómo funciona la máquina de estados?
- ¿Qué hace cada estado?
- ¿Cómo se acumula el puntaje entre niveles?

---

## 📝 NOTAS IMPORTANTES

1. **Siempre menciona:**
   - Herencia cuando veas `: public`
   - Composición cuando veas objetos como atributos
   - Encapsulamiento cuando veas `private`/`protected`
   - Polimorfismo cuando veas `virtual` y `override`

2. **Patrones comunes:**
   - Getters/Setters para atributos privados
   - Prefijo `_` en atributos privados
   - Métodos `const` que no modifican el objeto

3. **SFML:**
   - `sf::Drawable` para dibujar
   - `sf::Sprite` para imágenes
   - `sf::Texture` para cargar imágenes
   - `sf::Clock` para tiempo

---

## 🚀 SIGUIENTE PASO

¿Empezamos con **Jugador**? Es la clase más importante después de Entidad.




# Laboratorio2_robotica

## Importante
Para ver el video, tendra que descargar el ZIP y descomprimirlo
## Integrantes:

1. Maximiliano Esteban Miño Silva
2. Francisca Javiera Silva Castro
3. Tomás Abdiel Pérez Jeria
4. Matías Eliseo Villegas Muñoz

## Preguntas

### Parte 1: Configuración del Hardware y Pruebas Iniciales

1. ¿Qué es la percepción en robótica y por qué es fundamental en los sistemas autónomos?

    En robótica, la percepción es la capacidad que tiene el robot para recolectar datos del entorno o en algunos casos de su estado interno a través de sensores y transformarlos en información que es útil para interactuar, navegar o realizar otro tipo de tareas. Esta se divide en tres categorías: sensorial básica, especial y compleja. La primera permite detectar variables físicas como obstáculos, colores, formas, etc., la segunda; la posición en donde se encuentra el robot y qué hay en su entorno, y la tercera; reconocer objetos, personas, etc.

    La percepción, en los sistemas autónomos, es importante debido a que les  permite construir una representación del entorno (mapas) y usar esta información para planificar acciones y tomar decisiones de forma autónoma. 

2. En el sensor ultrasónico HC-SR04 ¿Qué parámetro se mide para calcular la distancia?

    Para calcular la distancia, el parámetro que se mide es el tiempo que tarda la onda de sonido ultrasónica en viajar desde el emisor hasta un objeto y regresar al receptor, en forma de eco, mediante la siguiente fórmula: distancia = $\frac{t*v}{2}$, donde $t$ representa el tiempo del pulso emitido en segundos y v representa la velocidad del sonido en el aire ( $343 \frac{m}{s}$)

3. ¿Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo podría reducirse?

    El ruido, en las mediciones del sensor ultrasónico, influye en la disminución de precisión y confiabilidad de las distancias detectadas, ya que existen variaciones aleatorias que son producidas por diferentes factores, como interferencias electromagnéticas, múltiples reflexiones de la onda ultrasónica, superficies irregulares o condiciones ambientales como temperatura. 

    Esto se puede reducir mediante la técnica de filtrado de datos, la cual suaviza la señal y mejora la calidad de la información otorgada por los sensores, con el objetivo de que el sistema autónomo evite tomar decisiones equivocadas. Existen tres tipos de esta técnica: filtro de media móvil (se promedian los últimos N valores de la señal original y otorga una señal suavizada), filtro de media ponderada (calcula una media en la que cada muestra tiene un peso diferente) y filtro pasa bajos (atenúa las frecuencias altas presentes en la señal).  

#### Reflexiones

Al hacer uso de el sensor RGB, en primera instancia, los numeros que nos entregaba eran relativamente elevados (entre 40-70 en un espacio con luz reducida), predominando el verde, ademas, los datos se disparaban en el momento de que se exponía a un lugar con luz, por lo que no nos era útil por los parametros que teníamos, por lo que aplicamos un filtro pasa bajos, reduciendo sonsiderablemente los valores y balanceandolos.

### Parte 2:Procesamiento de datos y Algoritmos de Navegación

1. Si el robot detecta el color rojo en el suelo ¿Qué acción debería tomar? ¿Por qué?

    En el caso de que el robot detecte el color rojo en el suelo, la acción que debe tomar va a depender del contexto o la lógica que fue implementada para el funcionamiento de este. Sin embargo, el color rojo generalmente es usado como una señal de peligro o de advertencia, por lo que el robot se programa para detenerse o cambiar de dirección para prevenir o más bien evitar que el robot tenga colisiones aumentando la seguridad y la confiabilidad en las acciones que realizará. De esta forma se puede aumentar la seguridad, confiabilidad y precisión. 

2. Si el sensor ultrasónico detecta valores erráticos ¿Qué estrategias podrías aplicar para mejorar la precisión?

    Las estrategias que se pueden aplicar para mejorar la precisión son:

    1. Calibración: mediante el ajuste de las mediciones para coincidir con un valor de referencia conocido corrige los errores sistemáticos. Para esto, se usan patrones de referencia, los que incluyen valores físicos, comparación con otros instrumentos ya calibrados y hace uso de entornos de prueba controlados, por ejemplo, que la temperatura sea la misma.

    2. Fusión de sensores: toma lo bueno de cada uno de los sensores y los fusiona. Esta puede ser por redundancia, es decir, cuando varios sensores miden lo mismo; por complementariedad, cada sensor proporciona una parte distinta de la información, y por sinergia, combinación de sensores

    3. Filtrado de datos: esta técnica se puede aplicar a través de tres tipos de filtro:
  
        -Media móvil
        
        -Media ponderada
        
        -Pasa-bajos

3. Si tuvieras que integrar un nuevo sensor para mejorar la navegación del robot ¿Cuál elegirías y por qué?

    Para mejorar la navegación del robot sería útil integrar el sensor LIDAR. Este emite pulsos de luz láser que viajan por el aire, rebota en algún objeto y luego regresa al sensor, y lo que hace el sensor es medir el tiempo que tarda en regresar cada pulso, calculando la distancia que recorre.
    
    Las razones por las que se elige este sensor son por la alta precisión que tiene en la detección de obstáculos, ya que puede generar un mapa 2D o 3D del entorno, con miles de puntos por segundo, también porque tiene un mayor alcance (100 metros o más) y tiene una menor sensibilidad a condiciones del entorno. Por ende, le permiten al robot construir un SLAM mucho más preciso, planificar rutas que eviten los obstáculos en tiempo real y poder reaccionar a cambios dinámicos en el entorno.

4. ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?

   El tiempo de respuesta del robot al detectar un cambio de color con un sensor TCS34725 (RGB) va de un rango desde los 10 a 100 milisegundos. Este rango depende totalmente de cómo está configurado el sensor y el software del robot como también del tiempo de integración (proceso en donde obtiene datos antes de procesarlos), ya que si se tiene un periodo muy corto, hay una respuesta más rápida pero menos precisa debido a que hay mayor sensibilidad al ruido. En cambio, si el periodo es más largo la precision es mucho más alta pero el robot tiene una reaccion más lenta frente a un cambio de color.

   Además, el tiempo total incluye el procesamiento del dato por parte del software del robot y la ejecución de una acción, por lo que optimizar el código y mantener lecturas constantes mejora la eficiencia de respuesta.

#### Reflexiones

Luego de realizar las calibraciones necesarias para el proceso de navegación (tanto como del sensor RGB como el ultrasónico), colocamos algunos obstáculos para que el robot tomara las desiciones que nosotros determinamos. Por un lado, el sensor ultrasónico funciono correctamente, detectando obstáculos adecuadamente, sin embargo, el sensor RGB lograba detectar colores, sin embargo, este tenía dificultades para detectar correctamente los colores (especificamente el color azul), además se quedaba con los valores obtenidos en una instancia X por 5 iteraciones. 

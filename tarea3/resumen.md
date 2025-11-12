Codiog Original: https://github.com/TheRealYoussef/Linux-Kernel-Module-for-Listing-Tasks/blob/master/ListTasksLinear.c 

- **"task_struct"**: Estructura de datos del kernel que representa un proceso
    ref: https://elixir.bootlin.com/linux/v6.17.6/source/include/linux/sched.h#L816

- **"list_head"**: Estructura de datos del kernel para implementar listas enlazadas
- **"printk"**: Función del kernel para imprimir mensajes (similar a printf pero para el kernel)
- **"KERN_INFO"**: Nivel de prioridad para mensajes del kernel
    tambien hay KERN_ALERT, KERN_ERR, KERN_WARNING, KERN_DEBUG, etc.
- %-20s significa que el argumento que espera es una string y que la debe imprimir asegurando un ancho mínimo de 20 caracteres alineado a la izquierda
- %ld significa que el argumento que espera es un long int
- %d significa que el argumento que espera es un int
- **"for_each_process"**: Macro que itera sobre todos los procesos del sistema
    ref: https://elixir.bootlin.com/linux/v6.17.6/source/include/linux/sched/signal.h#L635
- **"list_for_each"**: Macro que itera sobre una lista enlazada del kernel
- **"list_entry"**: Macro que obtiene un puntero a la estructura que contiene la lista
- **"task_state_to_char"**: Función que convierte el estado de un proceso a un carácter
- **"init_task"**: Estructura que representa el proceso init (primer proceso del sistema)
- **"module_init"**: Macro que registra la función de inicialización del módulo
- **"module_exit"**: Macro que registra la función de salida del módulo
- **"MODULE_LICENSE"**: Macro que define la licencia del módulo
- **"MODULE_DESCRIPTION"**: Macro que define la descripción del módulo
- **"MODULE_AUTHOR"**: Macro que define el autor del módulo

Características principales:
- ListTasksLinear.c: Recorre los procesos de forma lineal usando for_each_process
- ListTasksDFS.c: Recorre los procesos en profundidad (DFS) usando la estructura de árbol de procesos

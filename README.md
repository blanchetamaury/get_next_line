# Get_Next_Line

**Lecture ligne par ligne d’un fichier en C**

---

## 📋 Table des matières

- [Présentation](#présentation)  
- [Fonctionnalités](#fonctionnalités)  
- [Installation & Compilation](#installation--compilation)  
  - [Compilation obligatoire](#compilation-obligatoire)  
  - [Compilation bonus](#compilation-bonus)  
- [Utilisation](#utilisation)  
- [Exemple d’utilisation](#exemple-dutilisation)  

---

## Présentation

La fonction `get_next_line` permet de **lire récursivement** une ligne complète à chaque appel, depuis un descripteur de fichier.  
Chaque ligne retournée est allouée dynamiquement (`malloc`) et doit être libérée par l’utilisateur.
```
char	*get_next_line(int fd)
```
il prend le fd d'un fichier obtenu avec `open`. Le fd doit etre >= 0 pour etre valide.

## Fonctionnalités

- Lecture ligne par ligne sans charger tout le fichier en mémoire
- Gestion de plusieurs descripteurs de fichiers simultanément
- Taille de buffer paramétrable via la macro BUFFER_SIZE
- Gestion des cas d’erreur (lecture, allocation)


## Installation--Compilation

### Compilation obligatoire
```bash
git clone https://github.com/blanchetamaury/get_next_line.git
cd get_next_line
make
```

### Compilation bonus
```bash
git clone https://github.com/blanchetamaury/get_next_line.git
cd get_next_line
make bonus
```

## Utilisation

```
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Ligne lue : %s", line);
        free(line);
    }

    close(fd);
    return 0;
}

```

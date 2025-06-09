# HOI4 Prototype

Этот репозиторий содержит прототип стратегии в реальном времени, вдохновлённый Hearts of Iron IV. Проект изначально нацелен на кроссплатформенность и собирается при помощи CMake и компилятора C++17. В качестве основы используются SDL2 и OpenGL, а для разработки интерфейса применён Dear ImGui. Данный репозиторий также включает инструменты и минимальные игровые данные.

## Структура проекта
- **CMakeLists.txt** – корневой файл сборки, подключающий подсистемы и задающий строгие флаги компиляции (-Wall -Wextra -Werror).
- **external/** – сторонние зависимости, подтягиваемые через FetchContent: SDL2, SDL2_image, SDL2_ttf, glm, nlohmann_json и Dear ImGui.
- **engine/** – модуль движка: ядро (логирование, ECS, шина событий), графика (SDL + OpenGL) и оболочка ImGui.
- **game/** – игровые модули: данные (JSON описания стран, провинций, шаблонов дивизий), логика экономики и политики, AI, правила балансировки.
- **assets/** – вспомогательные текстуры, шрифты и прочие ресурсы-заглушки.
- **tools/** – консольные утилиты (компилятор карт, конвертер сохранений).
- **docs/** – документация по сборке и обзор дизайна.
- **tests/** – модульные тесты, использующие doctest.

## Основные возможности
- Простая система сущностей (ECS) без сторонних библиотек.
- Шина событий для обмена сообщениями между подсистемами.
- Отрисовка через SDL2/OpenGL, интерфейс разработки на базе ImGui.
- Экономика и политика стран в упрощённом виде.
- Сериализация состояния игры в сжатый JSON-файл.
- Набор CLI-инструментов для подготовки игровых данных.

## Сборка
### Настольные платформы (Linux/Windows)
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Android
Понадобится Android NDK r26 или новее. Пример вызова:
```bash
mkdir build-android && cd build-android
cmake .. -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-24
make -j$(nproc)
```
Более подробные инструкции находятся в каталоге `docs/`.

## Скрипт автоматической сборки
Ниже приведён Python-скрипт `build.py`, автоматизирующий сборку под Windows и Android. При запуске без аргументов он выводит меню выбора платформы, проверяет наличие необходимых инструментов и при необходимости устанавливает их автоматически.

```python
#!/usr/bin/env python3
import os, shutil, subprocess, sys

def run(cmd):
    print(' '.join(cmd))
    subprocess.check_call(cmd)

def ensure_tool(cmd, pkg):
    if shutil.which(cmd) is None:
        run(['sudo', 'apt-get', 'install', '-y', pkg])

def menu():
    print('1. Windows')
    print('2. Android (arm64)')
    return input('Номер: ').strip()

choice = menu()
if choice == '1':
    ensure_tool('x86_64-w64-mingw32-gcc', 'mingw-w64')
    run(['cmake', '--build', 'build-windows'])
elif choice == '2':
    ensure_tool('wget', 'wget')
    run(['cmake', '--build', 'build-android'])
else:
    sys.exit('Неверный выбор')
```


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
Ниже представлен пример Python-скрипта, который автоматизирует сборку проекта под Windows (через MinGW) и Android. Перед запуском убедитесь, что переменные окружения `ANDROID_NDK` и `MINGW_TOOLCHAIN` указывают на соответствующие каталоги.

```python
#!/usr/bin/env python3
import argparse
import os
import subprocess


def run(cmd, cwd=None):
    print(' '.join(cmd))
    subprocess.check_call(cmd, cwd=cwd)


def build_windows(build_dir, toolchain):
    os.makedirs(build_dir, exist_ok=True)
    run([
        'cmake', '-S', '.', '-B', build_dir,
        f'-DCMAKE_TOOLCHAIN_FILE={toolchain}',
        '-DCMAKE_BUILD_TYPE=Release'
    ])
    run(['cmake', '--build', build_dir, '--config', 'Release'])


def build_android(build_dir, ndk):
    toolchain = os.path.join(ndk, 'build', 'cmake', 'android.toolchain.cmake')
    os.makedirs(build_dir, exist_ok=True)
    run([
        'cmake', '-S', '.', '-B', build_dir,
        f'-DCMAKE_TOOLCHAIN_FILE={toolchain}',
        '-DANDROID_ABI=arm64-v8a',
        '-DANDROID_PLATFORM=android-24',
        '-DCMAKE_BUILD_TYPE=Release'
    ])
    run(['cmake', '--build', build_dir, '--config', 'Release'])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Сборка HOI4 Prototype')
    parser.add_argument('--windows', action='store_true', help='Собрать Windows-версию')
    parser.add_argument('--android', action='store_true', help='Собрать Android-версию')
    args = parser.parse_args()

    if args.windows:
        toolchain = os.environ.get('MINGW_TOOLCHAIN')
        if not toolchain:
            raise RuntimeError('Не задан MINGW_TOOLCHAIN')
        build_windows('build-windows', toolchain)

    if args.android:
        ndk = os.environ.get('ANDROID_NDK')
        if not ndk:
            raise RuntimeError('Не задан ANDROID_NDK')
        build_android('build-android', ndk)
```


#!/usr/bin/env python3
import argparse
import os
import shutil
import subprocess
import sys


def run(cmd, cwd=None):
    print(' '.join(cmd))
    subprocess.check_call(cmd, cwd=cwd)


def ensure_tool(cmd, package):
    if shutil.which(cmd):
        return
    print(f'Installing {package}...')
    run(['sudo', 'apt-get', 'update'])
    run(['sudo', 'apt-get', 'install', '-y', package])


def ensure_ndk():
    ndk = os.environ.get('ANDROID_NDK')
    if ndk and os.path.isdir(ndk):
        return ndk
    url = 'https://dl.google.com/android/repository/android-ndk-r26d-linux.zip'
    ndk_dir = os.path.join(os.getcwd(), 'android-ndk-r26d')
    if not os.path.isdir(ndk_dir):
        print('Downloading Android NDK r26d...')
        run(['wget', url, '-O', 'ndk.zip'])
        run(['unzip', '-q', 'ndk.zip'])
    os.environ['ANDROID_NDK'] = ndk_dir
    return ndk_dir


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

    if not args.windows and not args.android:
        print('Выберите цель сборки:')
        print('1. Windows')
        print('2. Android (arm64)')
        choice = input('Номер: ').strip()
        if choice == '1':
            args.windows = True
        elif choice == '2':
            args.android = True
        else:
            print('Неверный выбор')
            sys.exit(1)

    ensure_tool('cmake', 'cmake')
    ensure_tool('make', 'build-essential')
    ensure_tool('pkg-config', 'pkg-config')
    ensure_tool('freetype-config', 'libfreetype-dev')

    if args.windows:
        ensure_tool('x86_64-w64-mingw32-gcc', 'mingw-w64')
        toolchain = os.environ.get('MINGW_TOOLCHAIN')
        if not toolchain:
            tc = os.path.abspath('mingw-toolchain.cmake')
            if not os.path.exists(tc):
                with open(tc, 'w') as f:
                    f.write('set(CMAKE_SYSTEM_NAME Windows)\n')
                    f.write('set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)\n')
                    f.write('set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)\n')
            toolchain = tc
        build_windows('build-windows', toolchain)

    if args.android:
        ensure_tool('wget', 'wget')
        ensure_tool('unzip', 'unzip')
        ndk = ensure_ndk()
        build_android('build-android', ndk)

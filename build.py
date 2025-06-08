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

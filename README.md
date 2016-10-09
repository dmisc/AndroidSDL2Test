# AndroidSDL2Test

Android native GLES3 example project. Uses SDL2 for context initialization.

## Download and compile

```
git clone https://github.com/renanti/AndroidSDL2Test.git
cd AndroidSDL2Test/
git submodule update --init
cd external/SDL2 && git apply ../sdl2_android.patch && cd -
./gradlew build
```
Output apk is in app/build/outputs/apk dir.

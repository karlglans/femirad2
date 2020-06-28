FROM trzeci/emscripten:sdk-tag-1.38.25-64bit

CMD ["emcc", "/usr/src/app/main.cpp", "/usr/src/app/Board.cpp", "/usr/src/app/Game.cpp", \ 
  "/usr/src/app/Search.cpp", "/usr/src/app/GamestateNode.cpp", "/usr/src/app/Boardevaluator.cpp", \
  "-s", "WASM=1", "-o", "/usr/src/target/main.js", "-s", \
  "EXPORTED_FUNCTIONS=['_main', '_markEmptyCell', '_startNewGame', '_releaseApp', '_doNextMove']", \
  "-s", "EXTRA_EXPORTED_RUNTIME_METHODS=['getValue','setValue','ccall']"]
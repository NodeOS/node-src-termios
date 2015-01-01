{
  "targets": [
    {
      "target_name": "binding",
      "sources": [ "src/termios.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}

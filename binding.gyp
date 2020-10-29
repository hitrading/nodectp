{
  "targets": [
    {
      "target_name": "shifctp",
      "sources": [ "src/shifctp.cpp",  "src/ThostFtdcMdSpiI.cpp", "src/WrapMd.cpp",  "src/ThostFtdcTraderSpiI.cpp", "src/WrapTd.cpp"],
      "conditions": [
        ["OS=='linux'", {
          "libraries":["$(CURDIR)/../api/tradeapi_linux64/thostmduserapi_se.so", "$(CURDIR)/../api/tradeapi_linux64/thosttraderapi_se.so"],
          "include_dirs":["<!(node -e \"require('nan')\")", "api/tradeapi_linux64"]
        }],
        ["OS=='win'", {
          "conditions": [
            ["target_arch=='ia32'", {
              "libraries":["../api/tradeapi_windows/thostmduserapi_se.lib", "../api/tradeapi_windows/thosttraderapi_se.lib"],
              "include_dirs":["<!(node -e \"require('nan')\")", "api/tradeapi_windows"]
            }, { # target_arch=="x64"
              "libraries":["../api/tradeapi_windows64/thostmduserapi_se.lib", "../api/tradeapi_windows64/thosttraderapi_se.lib"],
              "include_dirs":["<!(node -e \"require('nan')\")", "api/tradeapi_windows64"]
            }]
          ]
        }]
      ]
    }
  ]
}

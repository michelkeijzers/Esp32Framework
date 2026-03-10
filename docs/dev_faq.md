# Compiler issues

# VS Code

# IDF Terminal

- Ctrl-Shift-P, select "ESP-IDF Terminal"

## Intellisense include issues (red underlines under #include)

- Ctrl-Shift-P, select "ESP-IDF Terminal"
- In terminal, type: idf.py build

Check c_cpp_properties.json :

```
      "includePath": [
        "${workspaceFolder}/**",
        "C:
        "C:/Users/i4studio/esp/v5.4.1/esp-idf/components/**/include",
        "C:/Users/i4studio/esp/v5.4.1/esp-idf/components/freertos/**",

      ],
```

Still did not work, so I disabled the squiggle warnings.

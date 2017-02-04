 /*
  * Copyright (C) 2017 Adrian DC
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Constants
#define WMIC_ENTITIES "wmic path Win32_PnPEntity"
#define WMIC_CAPTION "mbed"
#define WMIC_NAME "Serial Port (COM"

// Entrypoint
int main()
{
    // Variables
    FILE* buffer;
    size_t len;
    char output[40];
    char* port;

    // Request matching COM ports list
    buffer = popen(WMIC_ENTITIES " Where \"Caption LIKE '%%" WMIC_CAPTION
            " %%' AND Name LIKE '%%" WMIC_NAME "%%'\" GET Name", "r");

    // Read buffer output
    while (fgets(output, sizeof(output), buffer) != NULL) {

        // Filter header lines
        if (strstr(output, WMIC_NAME) != NULL) {

            // Parse ...(COM?)...
            port = strstr(output, "(") + 1;
            len = (strstr(output, ")") - port);

            // Output found COM port
            printf("%.*s", len, port);

            // Ignore next COM ports
            break;
        }
    }

    // Close command buffer
    pclose(buffer);
    return 0;
}

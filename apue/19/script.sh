#!/bin/bash
(echo "Script started on " `date`;./pty "${SHELL:-/bin/bash}";echo "Script done on " `date`) | tee typescript

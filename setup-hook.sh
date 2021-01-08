#!/bin/bash
echo "Adding commit hooks..."
  shopt -s nullglob
  for hook in *.hook; do
    ln -sf "$(pwd)/${hook}" ".git/hooks/${hook%.hook}"
done

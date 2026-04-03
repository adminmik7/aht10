#!/usr/bin/env bash
# start.sh — One-command setup & launch for AHT10 Monitor
# Checks/installs Python3 + pip if missing, then runs monitor.py

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MONITOR="${SCRIPT_DIR}/monitor.py"

# ─── Colors ──────────────────────────────────────────────
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

log_info()  { echo -e "${GREEN}[✓]${NC} $1"; }
log_warn()  { echo -e "${YELLOW}[!]${NC} $1"; }
log_error() { echo -e "${RED}[✗]${NC} $1"; }

# ─── Check monitor.py exists ──────────────────────────────
if [ ! -f "$MONITOR" ]; then
    log_error "monitor.py not found at: $MONITOR"
    exit 1
fi

# ─── Detect + install Python 3 ───────────────────────────
if ! command -v python3 &>/dev/null; then
    log_info "Python3 not found, installing..."
    if command -v apt-get &>/dev/null; then
        sudo apt-get update -qq && sudo apt-get install -y -qq python3 python3-pip
    elif command -v dnf &>/dev/null; then
        sudo dnf install -y -q python3 python3-pip
    else
        log_error "Please install Python3 manually."
        exit 1
    fi
    log_info "Python3 installed: $(python3 --version 2>&1)"
else
    log_info "Python3 found: $(python3 --version 2>&1)"
fi

# ─── Ensure pip3 works ───────────────────────────────────
if ! python3 -m pip --version &>/dev/null; then
    log_warn "pip not found, installing..."
    if command -v apt-get &>/dev/null; then
        sudo apt-get install -y -qq python3-pip
    else
        curl -sS https://bootstrap.pypa.io/get-pip.py | python3
    fi
    log_info "pip3 ready."
fi

# ─── Run monitor.py ───────────────────────────────────────
echo ""
echo "════════════════════════════════════════════════"
echo "  AHT10 Monitor  ESP-12E Temperature & Humidity"
echo "════════════════════════════════════════════════"
echo ""

if [ -n "$1" ]; then
    python3 "$MONITOR" "$1"
else
    python3 "$MONITOR"
fi

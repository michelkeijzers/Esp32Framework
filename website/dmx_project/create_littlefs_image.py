#!/usr/bin/env python3
"""
Helper script to create a LittleFS image from the website dist/ folder
Run this before flashing to ESP32, or let CMake run it automatically
"""

import os
import sys
import subprocess
import shutil

# Paths
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DIST_DIR = os.path.join(SCRIPT_DIR, "dist")
OUTPUT_IMAGE = os.path.join(SCRIPT_DIR, "littlefs_image.bin")
PARTITION_SIZE = 0x80000  # 512 KB in bytes (updated from 1 MB)

def check_mklittlefs():
    """Check if mklittlefs is available in ESP-IDF"""
    idf_path = os.environ.get("IDF_PATH")
    if not idf_path:
        print("Error: IDF_PATH not set. Please source the ESP-IDF environment.")
        return None
    
    # Common paths for mklittlefs
    possible_paths = [
        os.path.join(idf_path, "components/littlefs/littlefs/mklittlefs"),
        os.path.join(idf_path, "tools/mklittlefs/mklittlefs"),
        shutil.which("mklittlefs"),
    ]
    
    for path in possible_paths:
        if path and os.path.exists(path):
            return path
    
    return None

def create_littlefs_image():
    """Create LittleFS image from dist/ folder"""
    
    # Check if dist/ exists
    if not os.path.isdir(DIST_DIR):
        print(f"Error: dist/ folder not found at {DIST_DIR}")
        print("Please run 'npm run build' first.")
        return False
    
    # Check if mklittlefs is available
    mklittlefs = check_mklittlefs()
    if not mklittlefs:
        print("Warning: mklittlefs not found. You may need to manually create the LittleFS image.")
        print("Ensure ESP-IDF is properly installed and IDF_PATH is set.")
        print("NOTE: The ESP32 will format the littlefs partition on first boot if it's empty.")
        return True  # Don't fail the build if mklittlefs is unavailable
    
    # Get dist folder size
    total_size = 0
    for dirpath, dirnames, filenames in os.walk(DIST_DIR):
        for filename in filenames:
            filepath = os.path.join(dirpath, filename)
            total_size += os.path.getsize(filepath)
    
    print(f"Website size: {total_size / 1024:.1f} KB")
    if total_size > PARTITION_SIZE:
        print(f"Warning: Website exceeds partition size ({PARTITION_SIZE / 1024:.0f} KB)")
    
    # Create LittleFS image
    print(f"Creating LittleFS image: {OUTPUT_IMAGE}")
    try:
        cmd = [
            mklittlefs,
            "-c", DIST_DIR,
            "-s", str(PARTITION_SIZE),
            "-p", "256",
            "-b", "4096",
            OUTPUT_IMAGE
        ]
        subprocess.run(cmd, check=True)
        print("LittleFS image created successfully!")
        print(f"Image path: {OUTPUT_IMAGE}")
        return True
    except subprocess.CalledProcessError as e:
        print(f"Error creating LittleFS image: {e}")
        return False

if __name__ == "__main__":
    if not create_littlefs_image():
        sys.exit(1)

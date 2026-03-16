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


def copy_common_website_files():
    """Copy common website files from main/common/nodes/webserver/http_task/website/ to dist/"""
    # Path to common website files
    common_website_dir = os.path.join(SCRIPT_DIR, "../../main/common/nodes/webserver/http_task/website")
    common_website_dir = os.path.abspath(common_website_dir)
    
    if not os.path.isdir(common_website_dir):
        print(f"Warning: Common website directory not found at {common_website_dir}")
        print("Proceeding with app-specific files only.")
        return True
    
    print(f"Copying common website files from {common_website_dir}")
    try:
        for filename in os.listdir(common_website_dir):
            src = os.path.join(common_website_dir, filename)
            dst = os.path.join(DIST_DIR, filename)
            
            if os.path.isfile(src):
                # Copy file, overwriting if it exists
                shutil.copy2(src, dst)
                print(f"  Copied: {filename}")
            elif os.path.isdir(src) and filename != '__pycache__':
                # Skip if directory already exists in dist
                if os.path.exists(dst):
                    print(f"  Skipped directory: {filename} (already exists in dist)")
                else:
                    shutil.copytree(src, dst)
                    print(f"  Copied directory: {filename}")
        
        return True
    except Exception as e:
        print(f"Error copying common website files: {e}")
        return False


def copy_dmx_app_website_files():
    """Copy DMX app-specific website files from main/projects/dmx_controller/http_task/website/ to dist/"""
    # Path to DMX app-specific website files
    dmx_website_dir = os.path.join(SCRIPT_DIR, "../../main/projects/dmx_controller/http_task/website")
    dmx_website_dir = os.path.abspath(dmx_website_dir)
    
    if not os.path.isdir(dmx_website_dir):
        print(f"Warning: DMX app website directory not found at {dmx_website_dir}")
        print("Proceeding with common files only.")
        return True
    
    print(f"Copying DMX app website files from {dmx_website_dir}")
    try:
        for filename in os.listdir(dmx_website_dir):
            src = os.path.join(dmx_website_dir, filename)
            dst = os.path.join(DIST_DIR, filename)
            
            if os.path.isfile(src):
                # Copy file, overwriting if it exists
                shutil.copy2(src, dst)
                print(f"  Copied: {filename}")
            elif os.path.isdir(src) and filename != '__pycache__':
                # Copy directory, overwriting if it exists
                if os.path.exists(dst):
                    shutil.rmtree(dst)
                shutil.copytree(src, dst)
                print(f"  Copied directory: {filename}")
        
        return True
    except Exception as e:
        print(f"Error copying DMX app website files: {e}")
        return False


def create_littlefs_image():
    """Create LittleFS image from dist/ folder"""
    
    # Check if dist/ exists
    if not os.path.isdir(DIST_DIR):
        print(f"Error: dist/ folder not found at {DIST_DIR}")
        print("Please run 'npm run build' first.")
        return False
    
    # Copy common website files to dist/
    if not copy_common_website_files():
        print("Warning: Could not copy common website files")
    
    # Copy DMX app-specific website files to dist/
    if not copy_dmx_app_website_files():
        print("Warning: Could not copy DMX app website files")
    
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

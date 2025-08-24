use std::env;
use std::fs;
use std::path::Path;

fn get_folder_size(path: &Path) -> u64 {
    let mut size = 0;
    if path.is_dir() {
        for entry in fs::read_dir(path).expect("Unable to read the folder") {
            let entry = entry.expect("Error while reading the entry");
            let path = entry.path();
            if path.is_dir() {
                size += get_folder_size(&path);
            } else {
                size += fs::metadata(&path).map(|m| m.len()).unwrap_or(0);
            }
        }
    }
    size
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("sizeof <filename>");
        return;
    }

    let path = Path::new(&args[1]);

    let size: f64 = if path.is_file() {
        fs::metadata(path).expect("Error while getting file").len() as f64
    } else if path.is_dir() {
        get_folder_size(path) as f64  
    } else {
        eprintln!("The given path doesn't exist");
        return;
    };
    
    let units = ["B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"];
    let mut fsize = size;
    let mut unit_index = 0;

    while fsize >= 1024.0 && unit_index < units.len() - 1 {
        fsize /= 1024.0;
        unit_index += 1;
    }
    
    let formatted = if (fsize * 100.0).fract() == 0.0 {
        format!("{:.0}", fsize) // nincs tizedes
    } else if (fsize * 10.0).fract() == 0.0 {
        format!("{:.1}", fsize) // 1 tizedes
    } else {
        format!("{:.2}", fsize) // 2 tizedes
    };

    println!("{} {}", formatted, units[unit_index]);
}

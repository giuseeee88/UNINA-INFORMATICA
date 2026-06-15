import os
import argparse

def create_course_structure(year, semester, course_name, professor_name):
    # Standard folder names
    subfolders = [
        'slides',
        'appunti',
        'esercizi',
        'progetti',
        'esami',
        'libri',
        'contenuto-non-proprio'
    ]
    
    # Construct the path
    # We use the user's preferred naming convention for years and semesters
    year_dir = f"Primo Anno" if year == 1 else (f"Secondo Anno" if year == 2 else "Terzo Anno")
    sem_dir = f"Primo Semestre" if semester == 1 else "Secondo Semestre"
    
    base_path = os.path.join(year_dir, sem_dir, course_name, f"Prof-{professor_name}")
    
    print(f"Creating structure for: {base_path}")
    
    for folder in subfolders:
        path = os.path.join(base_path, folder)
        os.makedirs(path, exist_ok=True)
        # Create .gitkeep to ensure folders are tracked by git even if empty
        gitkeep_path = os.path.join(path, ".gitkeep")
        if not os.path.exists(gitkeep_path):
            with open(gitkeep_path, "w") as f:
                pass
                
    # Create a basic README for the course
    course_readme = os.path.join(year_dir, sem_dir, course_name, "README.md")
    if not os.path.exists(course_readme):
        with open(course_readme, "w") as f:
            f.write(f"# {course_name}\n\n")
            f.write(f"## Informazioni Corso\n")
            f.write(f"- **Anno:** {year}\n")
            f.write(f"- **Semestre:** {semester}\n")
            f.write(f"- **Stato:** ⏳ In Corso\n\n")
            f.write(f"## Professori\n")
            f.write(f"- Prof. {professor_name}\n")

    print("Structure created successfully!")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Genera la struttura standard per un nuovo corso.")
    parser.add_argument("--anno", type=int, required=True, help="Anno (1, 2, 3)")
    parser.add_argument("--semestre", type=int, required=True, help="Semestre (1, 2)")
    parser.add_argument("--corso", type=str, required=True, help="Nome del corso")
    parser.add_argument("--prof", type=str, required=True, help="Nome del professore")
    
    args = parser.parse_args()
    create_course_structure(args.anno, args.semestre, args.corso, args.prof)

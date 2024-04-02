import filecmp

def compare_files(file1, file2):
    if filecmp.cmp(file1, file2):
        print("Pass")
    else:
        print("Fail")

def main():
    filepairs = [("tests/reviewers.o1","myresults/output.o1"),
                 ("tests/reviewers.o2","myresults/output.o2"),
                 ("tests/reviewers.o3","myresults/output.o3"),
                 ("tests/reviewers.o4","myresults/output.o4"),
                 ("tests/reviewers.o5","myresults/output.o5"),
                 ("tests/reviewers.o6","myresults/output.o6"),
                 ("tests/reviewers.o7","myresults/output.o7"),
                 ("tests/reviewers.o8","myresults/output.o8"),
                 ("tests/reviewers.o9","myresults/output.o9"),]


    for filepair in filepairs:
        compare_files(filepair[0], filepair[1])
    

if __name__ == "__main__":
    main()

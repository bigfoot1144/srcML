var studentQuery1 =
    from student in students
    group student by student.Last[0];

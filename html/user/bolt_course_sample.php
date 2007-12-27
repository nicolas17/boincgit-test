<?php

require_once("../inc/bolt.inc");

function part2() {
    return sequence(
        name('inner seq'),
        lesson(
            name('lesson 3'),
            filename('bolt_sample_lesson3.php')
        )
    );
}

function basic_review() {
    return sequence(
        lesson(
            name('lesson 1'),
            filename('bolt_sample_lesson1.php')
        ),
        lesson(
            name('lesson 2'),
            filename('bolt_sample_lesson2.php')
        )
    );
}

function int_review() {
    return lesson(
        name('lesson 2'),
        filename('bolt_sample_lesson2.php')
    );
}

return sequence(
    name('course'),
    random(
        name('first lessons'),
        number(2),
        lesson(
            name('lesson 1'),
            filename('bolt_sample_lesson1.php')
        ),
        lesson(
            name('lesson 2'),
            filename('bolt_sample_lesson2.php')
        ),
        lesson(
            name('lesson 3'),
            filename('bolt_sample_lesson3.php')
        )
    ),
    exercise_set(
        exercise(
            name('exercise 1'),
            filename('bolt_sample_exercise1.php')
        ),
        refresh(array(7, 14, 28)),
        review(.3, basic_review()),
        review(.7, int_review())
    ),
    part2()
);

?>

#lang racket

(define (nonlat? lst)
  (cond [(null? lst) #t]
        [(atom? (car lst)) #f]
        [else (nonlat? (cdr lst))]))

(define (member-twice? atom lst)
  (cond [(null? lst) #f]
        [(eq? atom (car lst)) (if (member? atom (cdr lst)) #t #f)]
        [else (member-twice? atom (cdr lst))]))

(define (seconds lst)
  (cond [(null? lst) '()]
        [else (cons (cadr (car lst)) (seconds (cdr lst)))]))

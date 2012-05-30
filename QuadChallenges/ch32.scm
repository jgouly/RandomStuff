(define eps 0.001)

(define (my-tan x)
  (if (< x eps)
      x
      (let ((t2 (my-tan (/ x 2))))
	(/ (* 2 t2)
	   (- 1 (* t2 t2))))))


(define (find-smallest x)
  (let lewp ((n x) (i 0))
    (if (< n eps)
	(cons n i)
	(lewp (/ n 2) (+ i 1)))))


(define (tan-iter x)
  (let ((prep (find-smallest x))
	(my-tan (lambda (x) (/ (* 2 x)
			       (- 1 (* x x))))))
    (let lewp ((start (car prep)) (n (cdr prep)))
      (if (= 0 n)
	  start
	  (lewp (my-tan start) (- n 1))))))
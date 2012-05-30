(define eps 0.0001)

(define (my-tan x)
  (if (< x eps)
      (begin (display x) (newline) x)
      
      (let ((t2 (my-tan (/ x 2))))
	(/ (* 2 t2)
	   (- 1 (* t2 t2))))))



(define (do-tan x)
  (/ (* 2 x)
     (- 1 (* x x))))

(define (find-smallest x)
  (let lewp ((n x) (res '()))
    (if (< n eps)
	n
	(lewp (/ n 2) (cons n res)))))


(define (fuck-mgsk x)
  (let ((smallest (find-smallest x)))
    (let lewp ((start smallest) (current smallest))
      (if (>= current x)
	  start
	  (lewp (do-tan start) (* 2 current))))))

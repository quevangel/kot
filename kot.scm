(use-modules (sxml simple) (sxml match) (ice-9 pretty-print) (ice-9 textual-ports) (rnrs base))
(define kot-document-file-name (list-ref (command-line) 1))
(define (replace-special-chars obj)
  (if (not (list? obj)) obj
      (sxml-match obj
                  ((and) "&&")
                  ((amp) "&")
                  ((lt) "<")
                  ((gt) ">")
                  (,any (map replace-special-chars obj)))))
(define kot-document
  (with-input-from-file kot-document-file-name
    (lambda ()
      (xml->sxml (current-input-port)))))
(set! kot-document (replace-special-chars kot-document))
(define id->file-map (make-hash-table))
(define id->reftext-map (make-hash-table))
(define (append-to-reftext id obj)
  (assert (or (string? obj) (and (list? obj) (eq? 'insert (car obj)))))
  (let* ((rest-or-f (hash-ref id->reftext-map id))
         (rest (if rest-or-f rest-or-f '())))
    (hash-set! id->reftext-map id (cons obj rest))))
(define (process-reftext reftext id)
  (for-each (lambda (obj)
              (when (or (string? obj) (and (list? obj) (eq? (car obj) 'insert)))
                (append-to-reftext id obj)))
            reftext))
(define (process-deftext deftext)
  (sxml-match deftext
              ((deftext (@ (id ,id) . ,attrs) ,body ...)
               (let ((file (assoc-ref attrs 'file)))
                 (when file (hash-set! id->file-map id (car file)))
                 (for-each
                  (lambda (child-node)
                    (when (and (list? child-node) (eq? (car child-node) 'reftext))
                      (process-reftext child-node id)))
                  body)))))
(define (search-deftexts subtree)
  (when (list? subtree)
    (when (eq? (car subtree) 'deftext) (process-deftext subtree))
    (for-each search-deftexts subtree)))
(define (string-or-insert-to-link obj)
  (if (string? obj) obj
      (sxml-match-let (((insert (@ (text ,text))) obj))
                      (hash-ref id->reftext-map text))))
(define (link-reftext reftext)
  (let lp ((cell reftext))
    (unless (null? cell)
      (set-car! cell (string-or-insert-to-link (car cell)))
      (lp (cdr cell)))))
(define (unnest-text nested-text port)
  (cond ((string? nested-text) (put-string port nested-text))
        ((list? nested-text) (for-each (lambda (obj) (unnest-text obj port)) nested-text))))
; search for deftexts and append reftexts
(search-deftexts kot-document)
; reverse the reftexts as they were cons'd
(hash-for-each-handle (lambda (entry) (set-cdr! entry (reverse (cdr entry)))) id->reftext-map)
; link each insert to the corresponding reftext giving us a nested text
(hash-for-each (lambda (id reftext) (link-reftext reftext)) id->reftext-map)
; write each deftext that is associated with a file given the nested text
(hash-for-each (lambda (id file)
                 (let ((nested-text (hash-ref id->reftext-map id)))
                   (format #t "Writing to ~a\n" file)
                   (with-output-to-file file
                     (lambda () (unnest-text nested-text (current-output-port))))))
               id->file-map)

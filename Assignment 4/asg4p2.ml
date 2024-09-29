type 'a stack = 'a list

let empty = []

let is_empty s =
  s = []

let push x s =
  x :: s

let pop s =
  match s with
  | [] -> failwith "Stack is empty"
  | h::t -> (h, t)

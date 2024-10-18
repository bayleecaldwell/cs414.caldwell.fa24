type 'a priority_queue = Empty | Node of int * 'a * 'a priority_queue * 'a priority_queue

let empty = Empty

let is_empty pq =
  pq = Empty

let insert priority value pq =
  let rec merge t1 t2 =
    match (t1, t2) with
    | (Empty, _) -> t2
    | (_, Empty) -> t1
    | (Node (p1, v1, l1, r1), Node (p2, v2, l2, r2)) ->
      if p1 <= p2 then Node (p1, v1, merge l1 t2, r1)
      else Node (p2, v2, merge t1 l2, r2)
  in
  merge (Node (priority, value, Empty, Empty)) pq

let remove pq =
  match pq with
  | Empty -> failwith "Priority queue is empty"
  | Node (_, value, l, r) -> (value, merge l r)

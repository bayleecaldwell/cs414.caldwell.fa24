type 'a tree =
  | Empty
  | Node of 'a list * ('a tree) list

let rec height = function
  | Empty -> 0
  | Node (_, children) -> 1 + List.fold_left max 0 (List.map height children)

let rec in_order f = function
  | Empty -> ()
  | Node (keys, children) ->
    in_order f (List.hd children);
    List.iter2 (fun k c -> f k; in_order f c) keys (List.tl children);
    f (List.hd (List.rev keys));
    in_order f (List.hd (List.rev children))

let rec pre_order f = function
  | Empty -> ()
  | Node (keys, children) ->
    List.iter2 (fun k c -> f k; pre_order f c) keys children

let rec post_order f = function
  | Empty -> ()
  | Node (keys, children) ->
    List.iter2 (fun c k -> post_order f c; f k) children keys

let rec insert value = function
  | Empty -> Node ([value], [Empty; Empty])
  | Node (keys, children) as node ->
    if value < List.hd keys then
      Node (keys, (insert value (List.hd children)) :: List.tl children)
    else if value > List.hd (List.rev keys) then
      Node (keys, List.tl children @ [insert value (List.hd (List.rev children))])
    else
      let (k1, k2) = List.split (List.filter (fun k -> k < value) keys) in
      let (c1, c2) = List.split (List.filter (fun c -> c <> Empty) children) in
      Node ((k1 @ [value] @ k2), (c1 @ [insert value Empty] @ c2))

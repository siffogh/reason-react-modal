[%bs.raw {|require('./App.css')|}];

[@react.component]
let make = () =>
  <div className="App">
    <h1> {"Parent container" |> ReasonReact.string} </h1>
    <h3> {"This is just a demo container" |> ReasonReact.string} </h3>
    <button> {"open modal" |> ReasonReact.string} </button>
  </div>;
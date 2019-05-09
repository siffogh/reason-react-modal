[%bs.raw {|require('./App.css')|}];

[@react.component]
let make = () => {
  let (isModalVisible, setIsModalVisible) = React.useState(() => false);

  <div className="App">
    <h1> {"Parent container" |> ReasonReact.string} </h1>
    <h3> {"This is just a demo container" |> ReasonReact.string} </h3>
    <button onClick={_ => setIsModalVisible(_ => !isModalVisible)}>
      {"open modal" |> ReasonReact.string}
    </button>
    {!isModalVisible
       ? ReasonReact.null : <Modal> {"Foo" |> ReasonReact.string} </Modal>}
  </div>;
};
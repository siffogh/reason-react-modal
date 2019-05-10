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
       ? ReasonReact.null
       : <Modal onModalClose={_ => setIsModalVisible(_ => false)}>
           <Modal.Header> {"Header" |> ReasonReact.string} </Modal.Header>
           <Modal.Body> {"Body" |> ReasonReact.string} </Modal.Body>
           <Modal.Footer>
             <Modal.Footer.CloseBtn>
               {"Close" |> ReasonReact.string}
             </Modal.Footer.CloseBtn>
           </Modal.Footer>
         </Modal>}
  </div>;
};
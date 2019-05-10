[%bs.raw {|require('./Modal.css')|}];

[@bs.scope "document"] [@bs.val] external body: Dom.element = "body";

module Cross = {
  [@bs.module "./cross.svg"] [@react.component]
  external make: unit => React.element = "default";
};

let modalContext = React.createContext(() => ());

module ContextProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };

  let make = React.Context.provider(modalContext);
};

[@react.component]
let make = (~children, ~onModalClose) => {
  ReactDOMRe.createPortal(
    <div className="modal-container" role="dialog" ariaModal=true>
      <div className="modal-content">
        <ContextProvider value=onModalClose> children </ContextProvider>
      </div>
    </div>,
    body,
  );
};

module Header = {
  [@react.component]
  let make = (~children) => {
    let onModalClose = React.useContext(modalContext);

    <div className="modal-header">
      children
      <button
        className="cross-btn"
        title="close modal"
        onClick={_ => onModalClose()}>
        <Cross />
      </button>
    </div>;
  };
};

module Body = {
  [@react.component]
  let make = (~children) => <div className="modal-body"> children </div>;
};

module Footer = {
  [@react.component]
  let make = (~children) => <div className="modal-footer"> children </div>;

  module CloseBtn = {
    [@react.component]
    let make = (~children) => {
      let onModalClose = React.useContext(modalContext);

      <button
        className="close-btn"
        title="close modal"
        onClick={_ => onModalClose()}>
        children
      </button>;
    };
  };
};
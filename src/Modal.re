[%bs.raw {|require('./Modal.css')|}];

[@bs.scope "document"] [@bs.val] external body: Dom.element = "body";

module Cross = {
  [@bs.module "./cross.svg"] [@react.component]
  external make: unit => React.element = "default";
};

type modalContextType = ReactEvent.Mouse.t => unit;

let modalContext = React.createContext(_ => ());

module ContextProvider = {
  let make = modalContext->React.Context.provider;

  [@bs.obj]
  external makeProps:
    (
      ~value: modalContextType,
      ~children: React.element,
      ~key: string=?,
      unit
    ) =>
    {
      .
      "value": modalContextType,
      "children": React.element,
    } =
    "";
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
  let make = (~children=React.null) => {
    let onModalClose = React.useContext(modalContext);

    <div className="modal-header">
      children
      <button className="cross-btn" title="close modal" onClick=onModalClose>
        <Cross />
      </button>
    </div>;
  };
};

module Body = {
  [@react.component]
  let make = (~children=React.null) =>
    <div className="modal-body"> children </div>;
};

module Footer = {
  [@react.component]
  let make = (~children=React.null) =>
    <div className="modal-footer"> children </div>;

  module CloseBtn = {
    [@react.component]
    let make = (~children=React.null) => {
      let onModalClose = React.useContext(modalContext);

      <button className="close-btn" title="close modal" onClick=onModalClose>
        children
      </button>;
    };
  };
};
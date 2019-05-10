[%bs.raw {|require('./Modal.css')|}];

[@bs.scope "document"] [@bs.val] external body: Dom.element = "body";

module Cross = {
  [@bs.module "./cross.svg"] [@react.component]
  external make: unit => React.element = "default";
};

[@react.component]
let make = (~children) => {
  ReactDOMRe.createPortal(
    <div className="modal-container" role="dialog" ariaModal=true>
      <div className="modal-content"> children </div>
    </div>,
    body,
  );
};

module Header = {
  [@react.component]
  let make = (~children) => {
    <div className="modal-header">
      children
      <button className="cross-btn" title="close modal"> <Cross /> </button>
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
      <button className="close-btn" title="close modal"> children </button>;
    };
  };
};
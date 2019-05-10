[%bs.raw {|require('./Modal.css')|}];

[@bs.scope "document"] [@bs.val] external body: Dom.element = "body";

[@bs.scope "document"] [@bs.val]
external addKeybordEventListener:
  (string, ReactEvent.Keyboard.t => unit) => unit =
  "addEventListener";

[@bs.scope "document"] [@bs.val]
external removeKeybordEventListener:
  (string, ReactEvent.Keyboard.t => unit) => unit =
  "removeEventListener";

[@bs.scope "document"] [@bs.val]
external activeElement: Dom.element = "activeElement";

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
  let modalRef = React.useRef(Js.Nullable.null);

  let handleTabKey = e => {
    let current = React.Ref.current(modalRef);
    switch (Js.Nullable.toOption(current)) {
    | Some(element) =>
      let elementObj = ReactDOMRe.domElementToObj(element);
      let elements =
        elementObj##querySelectorAll(
          "a[href], button, textarea, input[type='text'], input[type='radio'], input[type='checkbox'], select",
        );
      let firstElement = elements[0];
      let lastElement = elements[elements##length - 1];

      if (!ReactEvent.Keyboard.shiftKey(e) && activeElement !== firstElement) {
        firstElement##focus();
        ReactEvent.Keyboard.preventDefault(e);
      };

      if (ReactEvent.Keyboard.shiftKey(e) && activeElement !== lastElement) {
        lastElement##focus();
        ReactEvent.Keyboard.preventDefault(e);
      };

    | None => ignore()
    };
  };

  let keyListenersMap =
    Js.Dict.fromArray([|("27", _ => onModalClose()), ("9", handleTabKey)|]);

  let effect = () => {
    let keyDownListener = e => {
      let keyCodeStr = ReactEvent.Keyboard.keyCode(e) |> string_of_int;

      switch (Js.Dict.get(keyListenersMap, keyCodeStr)) {
      | Some(eventListener) => eventListener(e)
      | None => ignore()
      };
    };

    addKeybordEventListener("keydown", keyDownListener);
    Some(() => removeKeybordEventListener("keyDown", keyDownListener));
  };

  React.useEffect(effect);

  ReactDOMRe.createPortal(
    <div className="modal-container" role="dialog" ariaModal=true>
      <div className="modal-content" ref={ReactDOMRe.Ref.domRef(modalRef)}>
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